//
//  VCText.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCRenderState;
class VCFont;

#include "VCIRenderable.h"
#include "VCFont.h"

// 1.00 MB
#define VC_TEXT_BUFFER_MAX_VERT_SIZE 50000

class VCTextBuffer : VCIRenderable
{
public:
	VCTextBuffer(VCFont* font);
	~VCTextBuffer(void);

	void Initialize();

	void DrawText( std::string text, VCPoint llPoint, GLubyte4 color );

	virtual VCRenderState* GetState();
	virtual void Render();

public:
	VCFont* Font;

private:
	GLuint m_VAO;
	GLuint m_VBO;
	GlyphVerticie m_verts[VC_TEXT_BUFFER_MAX_VERT_SIZE];
	int m_vCount;

};

