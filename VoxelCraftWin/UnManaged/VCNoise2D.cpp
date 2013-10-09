//
//  VCNoise2D.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCNoise2D.h"


VCNoise2D::VCNoise2D(void):
	Ints(NULL),
	Floats(NULL),
	Booleans(NULL)
{
}


VCNoise2D::~VCNoise2D(void)
{
}

void VCNoise2D::GenerateIntMap( int width, int height, float octaves, float persiatance, int minValue, int maxValue )
{
	Ints = (int*) malloc(sizeof(int) * width * height);

	//for (int i = 0; i < width; i++ )


	//float octave_noise_2d(const float octaves,
	//	const float persistence,
	//	const float scale,
	//	const float x,
	//	const float y);
}
