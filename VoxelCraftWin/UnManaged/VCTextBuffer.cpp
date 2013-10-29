//
//  VCText.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTextBuffer.h"
#include "VCRenderState.h"
#include "VCGLRenderer.h"
#include "VCLexicalEngine.h"


VCTextBuffer::VCTextBuffer( VCFont* font ):
	Font(font),
	m_VAO(0),
	m_VBO(0),
	m_vCount(0)
{

}

VCTextBuffer::~VCTextBuffer( void )
{

}

void VCTextBuffer::Initialize()
{
	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	ZERO_CHECK(m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glVertexAttribPointer( VC_ATTRIBUTE_POSITION,		3,	GL_SHORT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Position));

	glEnableVertexAttribArray(VC_ATTRIBUTE_TEX_COORD_0);
	glVertexAttribPointer( VC_ATTRIBUTE_TEX_COORD_0,	2,	GL_FLOAT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, UV));

	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
	glVertexAttribPointer( VC_ATTRIBUTE_COLOR,			4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Color));

	// Release
	glBindVertexArray(0);

	VCGLRenderer::Instance->RegisterIRenderable(this);
}

void VCTextBuffer::DrawText( std::string text, VCPoint llPoint, GLubyte4 color )
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
		m_vCount );					// Write Offset
}

VCRenderState* VCTextBuffer::GetState()
{
	return Font->RenderState;
}

void VCTextBuffer::Render()
{
	if (m_vCount == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GlyphVerticie) * m_vCount, m_verts , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vCount);
	glBindVertexArray(0);

	m_vCount = 0;
}
