//
//  VCFlatGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCIChunkGenerator.h"
#include "VCMarshalableObject.h"

class VCFlatGenerator : public VCIChunkGenerator, public VCMarshalableObject
{
public:
	VCFlatGenerator(void);
	~VCFlatGenerator(void);

	virtual bool GenerateToBuffer( VCBlock* buffer, int chunkX, int chunkY, int chunkZ );

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();

	// ===============================================================
};

// Interop
int VCInteropNewFlatGenerator();
void VCInteropReleaseFlatGenerator(int handle);

