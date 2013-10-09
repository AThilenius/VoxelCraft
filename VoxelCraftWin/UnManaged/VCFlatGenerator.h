//
//  VCFlatGenerator.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCIChunkGenerator.h"
#include "VCMarshalableObject.h"

class VCFlatGenerator : public VCIChunkGenerator, public VCMarshalableObject
{
public:
	VCFlatGenerator(void)
	{
		VCObjectStore::Instance->UpdatePointer(Handle, this);
	}

	~VCFlatGenerator(void)
	{

	}

	virtual bool GenerateToBuffer( VCBlock* buffer, int chunkX, int chunkY, int chunkZ )
	{
		int addativeY = chunkY * CHUNK_WIDTH;
		bool empty = true;

		for (int cx=0; cx < CHUNK_WIDTH; cx++ )
		{
			for (int cz=0; cz < CHUNK_WIDTH; cz++ )
			{
				for (int cy=0; cy < CHUNK_WIDTH; cy++ )
				{
					int wy = addativeY + cy;

					if ( wy >= 0 && wy <= 10)
					{
						int mod = (FastRandom() % 6) - 3;
						buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock(128 + mod, 128 + mod, 128 + mod);
						empty = false;
					}

					else
						buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock::Air;
                
				}
			}
		}

		return empty;
	}

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();

	// ===============================================================
};

// Interop
int VCInteropNewFlatGenerator();
void VCInteropReleaseFlatGenerator(int handle);

