//
//  VCText.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCIRenderable.h"
#include "VCGLRenderer.h"

class VCText : VCIRenderable
{
public:
	VCText(void) {}

	VCText(VCRenderState* state, GLuint vao, int vCount):
		RenderState(state),
		VAO(vao),
		VertCount(vCount)
	{
		VCGLRenderer::Instance->RegisterIRenderable(this);
	}

	~VCText(void)
	{
		VCGLRenderer::Instance->UnRegisterIRenderable(this);
	}

	virtual VCRenderState* GetState() 
	{ 
		return RenderState; 
	}

	virtual void Render()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, VertCount);
		glBindVertexArray(0);
	}

	VCRenderState* RenderState;
	GLuint VAO;
	int VertCount;

};

