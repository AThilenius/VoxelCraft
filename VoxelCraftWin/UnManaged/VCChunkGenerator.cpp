//
//  VCChunkGenerator.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCChunkGenerator.h"


VCChunkGenerator::VCChunkGenerator(int x, int y, int z):
	m_x(x),
	m_y(y),
	m_z(z)
{
}


VCChunkGenerator::~VCChunkGenerator(void)
{
}

void VCChunkGenerator::BuildHeightMapToBuffer ( int* buffer, float octaves, float persistence, float scale, float loBound, float hiBound, short offset )
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
                                                 ((float)m_x * (float)CHUNK_WIDTH) + xOff + offset,  // x-coord
                                                 ((float)m_y * (float)CHUNK_WIDTH) + yOff + offset); // y-coord
            
            buffer[FLATTEN_2D(xOff, yOff, LOG_CHUNK_WIDTH)] = fastfloor(depth);
        }
    }
}

void VCChunkGenerator::generateToBuffer ( byte* buffer )
{
	int stoneMap [CHUNK_WIDTH * CHUNK_WIDTH];
    int dirtMap [CHUNK_WIDTH * CHUNK_WIDTH];
    
    BuildHeightMapToBuffer(stoneMap, 3.0f, 1.0f, 0.005, (float)CHUNK_WIDTH * /*4.0f **/ 0.3, (float)CHUNK_WIDTH /** 4.0f*/ * 0.5, 0);
    BuildHeightMapToBuffer(dirtMap, 3.0f, 1.0f, 0.005, (float)CHUNK_WIDTH * /*4.0f **/ -0.1, (float)CHUNK_WIDTH * /*4.0f **/ 0.3, 42);
    
    for (int cx=0; cx < CHUNK_WIDTH; cx++ )
    {
        for (int cy=0; cy < CHUNK_WIDTH; cy++ )
        {
            for (int cz=0; cz < CHUNK_WIDTH; cz++ )
            {
                
                int stoneDepth = stoneMap[FLATTEN_2D(cx, cz, LOG_CHUNK_WIDTH)];
                int dirtDepth = dirtMap[FLATTEN_2D(cx, cz, LOG_CHUNK_WIDTH)];
                
				int wy = m_y * CHUNK_WIDTH + cy;

                if ( wy <= stoneDepth)
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = Block_Stone;

                else if ( dirtDepth > 0 && wy <= stoneDepth + dirtDepth )
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = Block_Dirt;

                else if ( wy == stoneDepth + dirtDepth + 1 )
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = Block_Grass;

                else
                    buffer[FLATTEN_CHUNK(cx, cy, cz)] = Block_Air;
                
            }
        }
    }
}
