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
		int cx = (x >> LOG_CHUNK_WIDTH) - ChunkZeroX;
		int cy = (y >> LOG_CHUNK_WIDTH) - ChunkZeroY;
		int cz = (z >> LOG_CHUNK_WIDTH) - ChunkZeroZ;

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

	void GetWorldBounds ( vec3* lower, vec3* upper )
	{
		lower->x = ChunkZeroX * CHUNK_WIDTH;
		lower->y = ChunkZeroY * CHUNK_WIDTH;
		lower->z = ChunkZeroZ * CHUNK_WIDTH;

		upper->x = lower->x + m_viewDistTwo * CHUNK_WIDTH;
		upper->y = lower->y + m_viewDistTwo * CHUNK_WIDTH;
		upper->z = lower->z + m_viewDistTwo * CHUNK_WIDTH;
	}

public:
	static VCWorld* Instance;
	int ChunkZeroX, ChunkZeroY, ChunkZeroZ;

private:
	int m_viewDistTwo;
	int m_logViewDistTwo;
	VCChunk** m_chunks;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
int VCInteropWorldGetBlock ( int x, int y, int z );