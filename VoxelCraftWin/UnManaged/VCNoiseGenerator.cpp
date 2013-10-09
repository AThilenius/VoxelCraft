//
//  VCNoiseGenerator.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCNoiseGenerator.h"


void VCNoiseGenerator::BuildHeightMapToBuffer ( int* buffer, float octaves, float persistence, float scale, float loBound, float hiBound, short offset, int x, int z )
{   
    for ( int xOff = 0; xOff < CHUNK_WIDTH; xOff ++ )
    {
        for ( int yOff = 0; yOff < CHUNK_WIDTH; yOff++ )
        {
            float depth = scaled_octave_noise_2d(octaves,
                                                 persistence,
                                                 scale,
                                                 loBound,
                                                 hiBound,
                                                 ((float)x * (float)CHUNK_WIDTH) + xOff + offset,  // x-coord
                                                 ((float)z * (float)CHUNK_WIDTH) + yOff + offset); // y-coord
            
            buffer[FLATTEN_2D(xOff, yOff, LOG_CHUNK_WIDTH)] = fastfloor(depth);
        }
    }
}

bool VCNoiseGenerator::GenerateToBuffer ( VCBlock* buffer, int chunkX, int chunkY,  int chunkZ )
{
	int stoneMap [CHUNK_WIDTH * CHUNK_WIDTH];
    int dirtMap [CHUNK_WIDTH * CHUNK_WIDTH];
    
    BuildHeightMapToBuffer(stoneMap, 2.0f, 2.0f, 0.005, 0, 10, 0, chunkX, chunkZ);
    BuildHeightMapToBuffer(dirtMap, 2.0f, 1.0f, 0.004, -5, 5, 4242, chunkX, chunkZ);

	//memset(stoneMap, 0, sizeof(int) * CHUNK_WIDTH * CHUNK_WIDTH);
	//memset(dirtMap, 0, sizeof(int) * CHUNK_WIDTH * CHUNK_WIDTH);

	int addativeY = chunkY * CHUNK_WIDTH;
	bool empty = true;

    for (int cx=0; cx < CHUNK_WIDTH; cx++ )
    {
		for (int cz=0; cz < CHUNK_WIDTH; cz++ )
        {
			for (int cy=0; cy < CHUNK_WIDTH; cy++ )
			{
                int stoneDepth = stoneMap[FLATTEN_2D(cx, cz, LOG_CHUNK_WIDTH)];
                int dirtDepth = dirtMap[FLATTEN_2D(cx, cz, LOG_CHUNK_WIDTH)];
                
				int wy = addativeY + cy;

				if ( wy <= stoneDepth)
				{
					int mod = (FastRandom() % 6) - 3;
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock(128 + mod, 128 + mod, 128 + mod);
					empty = false;
				}

				else if ( dirtDepth > 0 && wy <= stoneDepth + dirtDepth )
				{
					int mod = (FastRandom() % 6) - 3;
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock(92 + mod, 86 + mod, 37 + mod);
					empty = false;
				}

				/*else if ( wy == stoneDepth + dirtDepth + 1 )
				{
				int mod = (FastRandom() % 6) - 3;
				buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock(110 + mod, 163 + mod, 40 + mod);
				}*/

                else
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = VCBlock::Air;
                
            }
        }
    }

	return empty;
}

void VCNoiseGenerator::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.NoiseChunkGenerator::VCInteropNewNoiseGenerator",		(void*)VCInteropNewNoiseGenerator);
	mono_add_internal_call("VCEngine.NoiseChunkGenerator::VCInteropReleaseNoiseGenerator",	(void*)VCInteropReleaseNoiseGenerator);
}

int VCInteropNewNoiseGenerator()
{
	VCNoiseGenerator* ng = new VCNoiseGenerator();
	return ng->Handle;
}

void VCInteropReleaseNoiseGenerator( int handle )
{
	VCNoiseGenerator* obj = (VCNoiseGenerator*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}
