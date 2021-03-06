//
//  VCTextBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCTextBuffer;

#include <vector>

class VCTextBuilder
{
public:
	VCTextBuilder(void);
	~VCTextBuilder(void);

	void Initialize();
	void Reset();
	void DrawText( int font, std::string text, VCPoint llPoint, GLubyte4 color, float depthStep );

private:
	std::vector<VCTextBuffer*> m_bufferByFont;
};

