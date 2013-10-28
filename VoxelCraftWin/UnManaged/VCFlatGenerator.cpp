//
//  VCFlatGenerator.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCFlatGenerator.h"
#include "VCObjectStore.h"

VCFlatGenerator::VCFlatGenerator(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCFlatGenerator::~VCFlatGenerator( void )
{

}

bool VCFlatGenerator::GenerateToBuffer( VCBlock* buffer, int chunkX, int chunkY, int chunkZ )
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

				if ( wy == 0 )
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

void VCFlatGenerator::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.FlatChunkGenerator::VCInteropNewFlatGenerator",		(void*)VCInteropNewFlatGenerator);
	mono_add_internal_call("VCEngine.FlatChunkGenerator::VCInteropReleaseFlatGenerator",	(void*)VCInteropReleaseFlatGenerator);
}

int VCInteropNewFlatGenerator()
{
	VCFlatGenerator* ng = new VCFlatGenerator();
	return ng->Handle;
}

void VCInteropReleaseFlatGenerator( int handle )
{
	VCFlatGenerator* obj = (VCFlatGenerator*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}