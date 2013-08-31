//
//  VCBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

typedef enum : char
{
	Block_Unknown = 0,
	Block_Air = 1,
	Block_Dirt = 2

} BlockType;

class VCBlock
{
public:
	VCBlock(void);
	~VCBlock(void);

	GLbyte4 GetColor();

	BlockType Type;
};

