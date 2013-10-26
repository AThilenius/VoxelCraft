//
//  VCWorld.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define FLATTEN_WORLD(X,Y,Z) ((((Z << m_logViewDistTwo) + X) << m_logViewDistTwo ) + Y)
#define WORLD_ORDERED_ITTORATOR(xName,yName,zName) for ( int z = 0; z < m_viewDistTwo; z++ ) { int zName = ChunkZeroZ + z; for ( int x = 0; x < m_viewDistTwo; x++ ) { int xName = ChunkZeroX + x; for ( int y = 0; y < m_viewDistTwo; y++ ) { int yName = ChunkZeroY + y;

#include "PCH.h"
#include "VCBlock.h"
#include "VCWorld.h"
#include "VCChunk.h"
#include "VCMarshalableObject.h"
#include "VCIChunkGenerator.h"

struct Ray
{
	Ray() {}
	Ray(vec3 origin, vec3 direction, float maxDist) : Origin(origin), Direction(direction), MaxDistance(maxDist){}
	vec3 Origin;
	vec3 Direction;
	float MaxDistance;

};

struct RaycastHit
{
	float Distance;
	VCBlock Type;
	vec3 Normal;
	int X, Y, Z;

};

struct VCEditorFileHeader001
{
	int ChunkWidth;
	int WorldSizeX, WorldSizeY, WorldSizeZ;
	int ChunkZeroX, ChunkZeroY, ChunkZeroZ;
};

class VCWorld : public VCMarshalableObject
{
public:
	VCWorld();
	~VCWorld(void);

	void InitializeEmpty();
	void GenerateRegenerate();
	void Rebuild();

	void SetViewDistance(int viewDistTwo)
	{
		if (((viewDistTwo - 1) & viewDistTwo))
		{
			VC_ERROR("View distance must be a power of two!");
		}

		m_viewDistTwo = viewDistTwo;
		m_logViewDistTwo = std::log(m_viewDistTwo) / std::log(2);
	}

	VCBlock GetBlock ( int x, int y, int z )
	{
		// What chunk?
		int cx = (x >> LOG_CHUNK_WIDTH) - ChunkZeroX;
		int cy = (y >> LOG_CHUNK_WIDTH) - ChunkZeroY;
		int cz = (z >> LOG_CHUNK_WIDTH) - ChunkZeroZ;

		// Out of range?
		if (cx < 0 || cx >= m_viewDistTwo)
			return VCBlock::ErrorBlock;

		if (cy < 0 || cy >= m_viewDistTwo)
			return VCBlock::ErrorBlock;

		if (cz < 0 || cz >= m_viewDistTwo)
			return VCBlock::ErrorBlock;

		VCChunk* chunk = m_chunks[FLATTEN_WORLD(cx, cy, cz)];

		// Where in chunk?
		int lx = x & MASK_CHUNK_WIDTH;
		int ly = y & MASK_CHUNK_WIDTH;
		int lz = z & MASK_CHUNK_WIDTH;

		return chunk->GetBlock(lx, ly, lz);
	}

	void SetBlock ( int x, int y, int z, VCBlock block )
	{
		// What chunk?
		int cx = (x >> LOG_CHUNK_WIDTH) - ChunkZeroX;
		int cy = (y >> LOG_CHUNK_WIDTH) - ChunkZeroY;
		int cz = (z >> LOG_CHUNK_WIDTH) - ChunkZeroZ;

		// Out of range?
		if (cx < 0 || cx >= m_viewDistTwo)
			return;

		if (cy < 0 || cy >= m_viewDistTwo)
			return;

		if (cz < 0 || cz >= m_viewDistTwo)
			return;

		VCChunk* chunk = m_chunks[FLATTEN_WORLD(cx, cy, cz)];

		// Where in chunk?
		int lx = x & MASK_CHUNK_WIDTH;
		int ly = y & MASK_CHUNK_WIDTH;
		int lz = z & MASK_CHUNK_WIDTH;

		// If its on a chunk boundary, flag other chunk for rebuild
		if (lx == 0 && cx - 1 >= 0) m_chunks[FLATTEN_WORLD(cx - 1, cy, cz)]->NeedsRebuild = true;
		if (ly == 0 && cy - 1 >= 0) m_chunks[FLATTEN_WORLD(cx, cy - 1, cz)]->NeedsRebuild = true;
		if (lz == 0 && cz - 1 >= 0) m_chunks[FLATTEN_WORLD(cx, cy, cz - 1)]->NeedsRebuild = true;

		if (lx == CHUNK_WIDTH - 1 && cx + 1 < m_viewDistTwo) m_chunks[FLATTEN_WORLD(cx + 1, cy, cz)]->NeedsRebuild = true;
		if (ly == CHUNK_WIDTH - 1 && cy + 1 < m_viewDistTwo) m_chunks[FLATTEN_WORLD(cx, cy + 1, cz)]->NeedsRebuild = true;
		if (lz == CHUNK_WIDTH - 1 && cz + 1 < m_viewDistTwo) m_chunks[FLATTEN_WORLD(cx, cy, cz + 1)]->NeedsRebuild = true;

		return chunk->SetBlock(lx, ly, lz, block);
	}

	// ===== Serialization ======================================================
	void Save (ofstream& stream);
	void Load (ifstream& stream);
	
	// ===== Physics ======================================================
	void GetWorldBounds ( vec3* lower, vec3* upper )
	{
		lower->x = ChunkZeroX * CHUNK_WIDTH;
		lower->y = ChunkZeroY * CHUNK_WIDTH;
		lower->z = ChunkZeroZ * CHUNK_WIDTH;

		upper->x = lower->x + m_viewDistTwo * CHUNK_WIDTH;
		upper->y = lower->y + m_viewDistTwo * CHUNK_WIDTH;
		upper->z = lower->z + m_viewDistTwo * CHUNK_WIDTH;
	}

	bool RaycastWorld(Ray ray, RaycastHit* hit);

public:
	int ChunkZeroX, ChunkZeroY, ChunkZeroZ;
	VCIChunkGenerator* ChunkGenerator;

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
int VCInteropNewWorld();
void VCInteropReleaseWorld(int handle);

void VCInteropWorldSetGenerator(int wHandle, int cHandle);
void VCInteropWorldSetViewDist(int handle, int distance);
void VCInteropWorldInitializeEmpty(int handle);
void VCInteropWorldGenerateRegenerate(int handle);
void VCInteropWorldRebuild(int handle);

void VCInteropWorldSaveToFile (int handle, MonoString* path);
void VCInteropWorldLoadFromFile (int handle, MonoString* path);

VCInteropBlock VCInteropWorldGetBlock (int handle, int x, int y, int z );
void VCInteropWorldSetBlock (int handle, int x, int y, int z, VCInteropBlock block);
int VCInteropWorldRaycast(int handle, Ray ray, RaycastHit* hitOut);