//
//  VCText.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCRenderState;

#include "VCIRenderable.h"

class VCText : VCIRenderable
{
public:
	VCText(void);
	VCText(VCRenderState* state, GLuint vao, GLuint vbo, int vCount, int width, int height);
	~VCText(void);

	virtual VCRenderState* GetState();
	virtual void Render();

	int TotalWidth;
	int TotalHeight;
	VCRenderState* RenderState;
	GLuint VAO;
	int VertCount;

private:
	GLuint m_vbo;

};

