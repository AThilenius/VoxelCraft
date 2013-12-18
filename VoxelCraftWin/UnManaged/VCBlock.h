//
//  VCBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCBlock
{
public:
	VCBlock(void);
	VCBlock(vcint4 interopBlock);
	VCBlock(GLubyte r, GLubyte g, GLubyte b);
	VCBlock(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	~VCBlock(void);

	bool IsTrasparent();
	bool IsTranslucent();
	bool IsSolid();
	vcint4 AsInterop();

	// Statics:
	static VCBlock ErrorBlock;
	static VCBlock Air;

	GLubyte4 Color;
};