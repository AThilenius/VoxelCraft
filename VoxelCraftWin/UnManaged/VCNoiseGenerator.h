//
//  VCNoiseGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCBlock;

#include "VCMarshalableObject.h"
#include "VCIChunkGenerator.h"

class VCNoiseGenerator : public VCIChunkGenerator, public VCMarshalableObject
{
public:
	VCNoiseGenerator();
	~VCNoiseGenerator();

	virtual bool GenerateToBuffer ( VCBlock* buffer, int chunkX, int chunkY, int chunkZ );

private:
	void BuildHeightMapToBuffer ( int* buffer, float octaves, float persistence, float scale, float loBound, float hiBound, short offset, int x, int z );

};

// Interop
DLL_EXPORT_API int VCInteropNewNoiseGenerator();
DLL_EXPORT_API void VCInteropReleaseNoiseGenerator(int handle);

