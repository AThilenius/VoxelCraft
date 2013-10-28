//
//  VCText.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCText.h"
#include "VCRenderState.h"
#include "VCGLRenderer.h"


VCText::VCText( void )
{

}

VCText::VCText( VCRenderState* state, GLuint vao, GLuint vbo, int vCount, int width, int height ) :
	RenderState(state),
	VAO(vao),
	m_vbo(vbo),
	VertCount(vCount),
	TotalWidth(width),
	TotalHeight(height)
{
	VCGLRenderer::Instance->RegisterIRenderable(this);
}

VCText::~VCText( void )
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &m_vbo);

	VCGLRenderer::Instance->UnRegisterIRenderable(this);
}

VCRenderState* VCText::GetState()
{
	return RenderState;
}

void VCText::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, VertCount);
	glBindVertexArray(0);
}
