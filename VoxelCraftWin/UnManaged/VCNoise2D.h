//
//  VCNoise2D.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

class VCNoise2D
{
public:
	VCNoise2D(void);
	~VCNoise2D(void);

	// Multi-octave Simplex noise
	// For each octave, a higher frequency/lower amplitude function will be added to the original.
	// The higher the persistence [0-1], the more of each succeeding octave will be added.
	void GenerateIntMap(int width, int height, float octaves, float persiatance, int minValue, int maxValue);

	int* Ints;
	float* Floats;
	bool* Booleans;
};

