//
//  VCTextBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCText;

#include <vector>
#include "VCAllPrimitives.h"

// 1.44 MB - 10,000 Characters
#define VC_TEXT_MAX_VERT_SIZE 60000

class VCTextBuilder
{
public:
	VCTextBuilder(void);
	~VCTextBuilder(void);

	void Reset();
	void Initialize();
	void DrawText( std::string text, Point llPoint, std::string font = "Cambria-16", GLubyte4 color = GLubyte4(255, 255, 255, 255) );

private:
	std::vector<VCText*> m_text;
};

