//
//  VCChunkGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCBlock.h"
#include "SimplexNoise.h"

class VCChunkGenerator
{
public:
	VCChunkGenerator(int x, int y, int z);
	~VCChunkGenerator(void);

	void BuildHeightMapToBuffer ( int* buffer, float octaves, float persistence, float scale, float loBound, float hiBound, short offset );
	void generateToBuffer ( byte* buffer );

private:
	int m_x, m_y, m_z;
};

