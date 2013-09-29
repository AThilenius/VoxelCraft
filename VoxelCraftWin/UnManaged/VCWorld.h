//
//  VCWorld.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define FLATTEN_WORLD(X,Y,Z) ((((Z << m_logViewDistTwo) + X) << m_logViewDistTwo ) + Y)
#define WORLD_ORDERED_ITTORATOR(xName,yName,zName) for ( int zName = 0; zName < m_viewDistTwo; zName++ ){ for ( int xName = 0; xName < m_viewDistTwo; xName++ ){ for ( int yName = 0; yName < m_viewDistTwo; yName++ ) {

#include "VCBlock.h"
#include "VCWorld.h"
#include "VCChunk.h"


class VCWorld
{
public:
	VCWorld(int viewDistance);
	~VCWorld(void);

	void Initialize();
	BlockType GetBlock ( int x, int y, int z )
	{
		// What chunk?
		int cx = (x >> LOG_CHUNK_WIDTH) - m_c0x;
		int cy = (y >> LOG_CHUNK_WIDTH) - m_c0y;
		int cz = (z >> LOG_CHUNK_WIDTH) - m_c0z;

		// Out of range?
		if (cx < 0 || cx >= m_viewDistTwo)
			return Block_Unknown;

		if (cy < 0 || cy >= m_viewDistTwo)
			return Block_Unknown;

		if (cz < 0 || cz >= m_viewDistTwo)
			return Block_Unknown;

		VCChunk* chunk = m_chunks[FLATTEN_WORLD(cx, cy, cz)];

		// Where in chunk?
		int lx = x & MASK_CHUNK_WIDTH;
		int ly = y & MASK_CHUNK_WIDTH;
		int lz = z & MASK_CHUNK_WIDTH;

		return chunk->GetBlock(lx, ly, lz);
	}

private:
	int m_viewDistTwo;
	int m_logViewDistTwo;
	int m_c0x, m_c0y, m_c0z;
	VCChunk** m_chunks;

};

