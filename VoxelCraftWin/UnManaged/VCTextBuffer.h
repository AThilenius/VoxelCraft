//
//  VCText.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCRenderStage;
class VCFont;
class VCGLBuffer;

#include "VCFont.h"

// 1.00 MB
#define VC_TEXT_BUFFER_MAX_VERT_SIZE 50000

class VCTextBuffer
{
public:
	VCTextBuffer(VCFont* font);
	~VCTextBuffer(void);

	void Initialize();

	void DrawText( std::string text, VCPoint llPoint, GLubyte4 color, float depthStep );

public:
	void Render();
	VCFont* Font;

private:
	VCRenderStage* m_renderStage;
	GlyphVerticie m_verts[VC_TEXT_BUFFER_MAX_VERT_SIZE];
	VCGLBuffer* m_glBuffer;
	int m_vCount;

};

