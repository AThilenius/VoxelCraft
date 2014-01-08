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
#include "VCShader.h"
#include "VCWindow.h"
#include "VCGui.h"
#include "VCResourceManager.h"


VCTextBuffer::VCTextBuffer( VCFont* font ):
	Font(font),
	m_VAO(0),
	m_VBO(0),
	m_vCount(0),
	m_renderStage(NULL)
{

}

VCTextBuffer::~VCTextBuffer( void )
{

}

void VCTextBuffer::Initialize()
{
	// Create Render Stage
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VCTextBuffer, &VCTextBuffer::Render>(this));
	m_renderStage->BatchOrder = VC_BATCH_GUI + 2;
	m_renderStage->Shader = VCResourceManager::GetShader("Lex");
	m_renderStage->Texture = Font->m_ddsTexture;
	VCGLRenderer::Instance->RegisterStage(m_renderStage);

	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	ZERO_CHECK(m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VCShaderAttribute::Position0);
	glVertexAttribPointer( VCShaderAttribute::Position0,		3,	GL_SHORT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Position));

	glEnableVertexAttribArray(VCShaderAttribute::TexCoord0);
	glVertexAttribPointer( VCShaderAttribute::TexCoord0,	2,	GL_FLOAT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, UV));

	glEnableVertexAttribArray(VCShaderAttribute::Color0);
	glVertexAttribPointer( VCShaderAttribute::Color0,			4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Color));

	// Release
	glBindVertexArray(0);
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
	VCShader::BoundShader->SetModelMatrix(glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -100000, -1));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GlyphVerticie) * m_vCount, m_verts , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vCount);
	glBindVertexArray(0);

	m_vCount = 0;
}
