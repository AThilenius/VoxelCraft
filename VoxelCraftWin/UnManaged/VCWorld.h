//
//  VCWorld.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCBlock.h"
#include "VCWorld.h"
#include "VCChunk.h"
#include "VCMarshalableObject.h"
#include "VCIChunkGenerator.h"

#define FLATTEN_WORLD(X,Y,Z) ((((Z << m_logViewDistTwo) + X) << m_logViewDistTwo ) + Y)
#define WORLD_ORDERED_ITTORATOR(xName,yName,zName) for ( int z = 0; z < m_viewDistTwo; z++ ) { int zName = ChunkZeroZ + z; for ( int x = 0; x < m_viewDistTwo; x++ ) { int xName = ChunkZeroX + x; for ( int y = 0; y < m_viewDistTwo; y++ ) { int yName = ChunkZeroY + y;

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

inline float IntBound ( float s, float ds )
{
	if (ds < 0)
	{
		s = -s;
		ds = -ds;
	}

	if (s < 0)
		s = 1 + (s - (long)s);

	else
		s = s - (long)s;

	return (1 - s) / ds;
}

class VCWorld : public VCMarshalableObject
{
public:
	VCWorld();
	~VCWorld(void);

	void Initialize();
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

	void SetGenerator(VCIChunkGenerator* generator) { ChunkGenerator = generator; }

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

		return chunk->SetBlock(lx, ly, lz, block);
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

	bool RaycastWorld(Ray ray, RaycastHit* hit)
	{
		vec3 wLoBound, wHiBound;
		GetWorldBounds(&wLoBound, &wHiBound);

		// Normalize Direction
		ray.Direction = normalize(ray.Direction);

		// Cube containing origin point.
		int x = FAST_FLOOR(ray.Origin.x);
		int y = FAST_FLOOR(ray.Origin.y);
		int z = FAST_FLOOR(ray.Origin.z);

		// Break out direction vector.
		float dx = ray.Direction.x;
		float dy = ray.Direction.y;
		float dz = ray.Direction.z;

		// Direction to increment x,y,z when stepping.
		float stepX = (0.0f < dx) - (dx < 0.0f);
		float stepY = (0.0f < dy) - (dy < 0.0f);
		float stepZ = (0.0f < dz) - (dz < 0.0f);

		// See description above. The initial values depend on the fractional
		// part of the origin.
		float tMaxX = IntBound(ray.Origin.x, dx);
		float tMaxY = IntBound(ray.Origin.y, dy);
		float tMaxZ = IntBound(ray.Origin.z, dz);

		// The change in t when taking a step (always positive).
		float tDeltaX = stepX/dx;
		float tDeltaY = stepY/dy;
		float tDeltaZ = stepZ/dz;

		// Buffer for reporting faces to the callback.
		vec3 face;

		// Avoids an infinite loop.
		if (dx == 0 && dy == 0 && dz == 0)
		{
			cout << "Attempted to ray-cast with a zero direction vector." << endl;
			return false;
		}

		while (/* ray has not gone past bounds of world */
			(stepX > 0 ? x < wHiBound.x : x >= wLoBound.x) &&
			(stepY > 0 ? y < wHiBound.y : y >= wLoBound.y) &&
			(stepZ > 0 ? z < wHiBound.z : z >= wLoBound.z)) 
		{

			// Already in world and hit a block?
			if (!(x < wLoBound.x || y < wLoBound.y || z < wLoBound.z || x >= wHiBound.x || y >= wHiBound.y || z >= wHiBound.z) && 
				!GetBlock(x, y, z).IsTrasparent() )
			{
				// Hit!
				hit->Normal = face;
				hit->Type = GetBlock(x, y, z);
				hit->X = x;
				hit->Y = y;
				hit->Z = z;

				if (tMaxX < tMaxY) 
					if (tMaxX < tMaxZ) 
						hit->Distance = tMaxX;
					else
						hit->Distance = tMaxZ;

				else 
					if (tMaxY < tMaxZ) 
						hit->Distance = tMaxY;
					else 
						hit->Distance = tMaxZ;

				return true;
			}

			// tMaxX stores the t-value at which we cross a cube boundary along the
			// X axis, and similarly for Y and Z. Therefore, choosing the least tMax
			// chooses the closest cube boundary. Only the first case of the four
			// has been commented in detail.
			if (tMaxX < tMaxY) 
			{
				if (tMaxX < tMaxZ) 
				{
					if (tMaxX > ray.MaxDistance) 
						break;

					// Update which cube we are now in.
					x += stepX;
					// Adjust tMaxX to the next X-oriented boundary crossing.
					tMaxX += tDeltaX;
					// Record the normal vector of the cube face we entered.
					face = vec3(-stepX, 0, 0);
				} 

				else 
				{
					if (tMaxZ > ray.MaxDistance) 
						break;

					z += stepZ;
					tMaxZ += tDeltaZ;
					face = vec3(0, 0, -stepZ);
				}
			} 

			else 
			{
				if (tMaxY < tMaxZ) 
				{

					if (tMaxY > ray.MaxDistance) 
						break;

					y += stepY;
					tMaxY += tDeltaY;
					face = vec3(0, -stepY, 0);
				} 

				else 
				{
					// Identical to the second case, repeated for simplicity in
					// the conditionals.
					if (tMaxZ > ray.MaxDistance) 
						break;

					z += stepZ;
					tMaxZ += tDeltaZ;
					face = vec3(0, 0, -stepZ);
				}
			}
		}

		return false;
	}

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
void VCInteropWorldInitialize(int handle);
void VCInteropWorldGenerateRegenerate(int handle);
void VCInteropWorldRebuild(int handle);
VCInteropBlock VCInteropWorldGetBlock (int handle, int x, int y, int z );
void VCInteropWorldSetBlock (int handle, int x, int y, int z, VCInteropBlock block);
int VCInteropWorldRaycast(int handle, Ray ray, RaycastHit* hitOut);