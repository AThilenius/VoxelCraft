//
//  VCText.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTextBuffer.h"
#include "VCGLRenderer.h"
#include "VCLexicalEngine.h"
#include "VCRenderStage.h"
#include "VCGLShader.h"
#include "VCWindow.h"
#include "VCGui.h"
#include "VCResourceManager.h"
#include "VCGLBuffer.h"


VCTextBuffer::VCTextBuffer( VCFont* font ):
	Font(font),
	m_vCount(0),
	m_renderStage(NULL),
	m_glBuffer(NULL)
{

}

VCTextBuffer::~VCTextBuffer( void )
{
	SAFE_DELETE(m_renderStage);
}

void VCTextBuffer::Initialize()
{
	// Create Render Stage
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VCTextBuffer, &VCTextBuffer::Render>(this));
	m_renderStage->BatchOrder = VC_BATCH_GUI + 2;
	m_renderStage->Shader = VCResourceManager::GetShader("Lex");
	m_renderStage->Texture = Font->m_ddsTexture;
	VCGLRenderer::Instance->RegisterStage(m_renderStage);

	m_glBuffer = new VCGLBuffer();
	m_glBuffer->VertexBufferSpecification()
		.SetVertexAttribute(VCShaderAttribute::Position0,	3, VCGLPrimitives::Short,			false,	sizeof(GlyphVerticie),	offsetof(GlyphVerticie, Position))
		.SetVertexAttribute(VCShaderAttribute::TexCoord0,	2, VCGLPrimitives::Float,			false,	sizeof(GlyphVerticie),	offsetof(GlyphVerticie, UV))
		.SetVertexAttribute(VCShaderAttribute::Color0,		4, VCGLPrimitives::UnsignedByte,	false,	sizeof(GlyphVerticie),	offsetof(GlyphVerticie, Color));
}

void VCTextBuffer::DrawText( std::string text, VCPoint llPoint, GLubyte4 color, float depthStep )
{
	if (m_vCount + text.size() >= VC_TEXT_BUFFER_MAX_VERT_SIZE)
	{
		VC_ERROR("VCTextBuffer Overflow: You probably have text drawing in a infinite loop.");
	}

	m_vCount += VCLexicalEngine::Instance->MakeTextToQuadBuffer(
		Font->FontID,				// Font ID
		text,						// Text
		llPoint,					// Location
		color,						// Color
		m_verts,					// Buffer
		m_vCount,					// Write Offset
		depthStep);					// Depth
}

void VCTextBuffer::Render()
{
	if (m_vCount == 0)
		return;

	// Scaling is handed in managed code for text, skip ViewProj and just use MVP
	VCGLShader::BoundShader->SetModelMatrix(glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -100000, -1));

	m_glBuffer->VertexBufferSpecification()
		.SetVertexData(sizeof(GlyphVerticie) * m_vCount, m_verts, m_vCount);

	m_glBuffer->Draw();

	m_vCount = 0;
}
