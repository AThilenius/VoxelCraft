//
//  VCIChunkGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "VCBlock.h"

class VCIChunkGenerator
{
public:
	virtual ~VCIChunkGenerator(void){}
	virtual bool GenerateToBuffer ( VCBlock* buffer, int chunkX, int chunkY, int chunkZ ) = 0;
};