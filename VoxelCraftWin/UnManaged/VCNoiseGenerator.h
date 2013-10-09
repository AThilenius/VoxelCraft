//
//  VCNoiseGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCBlock.h"
#include "SimplexNoise.h"
#include "VCIChunkGenerator.h"
#include "VCMarshalableObject.h"

class VCNoiseGenerator : public VCIChunkGenerator, public VCMarshalableObject
{
public:
	VCNoiseGenerator()
	{
		VCObjectStore::Instance->UpdatePointer(Handle, this);
	}

	~VCNoiseGenerator()
	{

	}

	virtual bool GenerateToBuffer ( VCBlock* buffer, int chunkX, int chunkY, int chunkZ );

private:
	void BuildHeightMapToBuffer ( int* buffer, float octaves, float persistence, float scale, float loBound, float hiBound, short offset, int x, int z );

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();

	// ===============================================================
};

// Interop
int VCInteropNewNoiseGenerator();
void VCInteropReleaseNoiseGenerator(int handle);

