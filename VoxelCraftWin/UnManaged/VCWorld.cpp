//
//  VCWorld.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCWorld.h"

#include "VCChunk.h"
#include "VCBlock.h"
#include "VCSceneGraph.h"
#include "VCDebug.h"
#include "VCStreamHelpers.h"
#include "VCIChunkGenerator.h"
#include "VCPhysics.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"

float IntBound ( float s, float ds )
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

VCWorld::VCWorld():
	ChunkZeroX(0),
	ChunkZeroY(0),
	ChunkZeroZ(0),
	ChunkGenerator(NULL),
	m_chunks(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCWorld::~VCWorld(void)
{
	if (m_chunks != NULL)
	{
		WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
			m_chunks[FLATTEN_WORLD(x ,y, z)]->SetParent(NULL);
			delete m_chunks[FLATTEN_WORLD(x ,y, z)];
		}}}

		free(m_chunks);
	}
}

void VCWorld::InitializeEmpty()
{
	m_chunks = (VCChunk**) malloc ( sizeof(VCChunk*) * m_viewDistTwo * m_viewDistTwo * m_viewDistTwo );

	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)] = new VCChunk(cX, cY, cZ, this);
		m_chunks[FLATTEN_WORLD(x ,y, z)]->SetParent(VCSceneGraph::Instance->RootNode);
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Initialize();
	}}}
}

void VCWorld::GenerateRegenerate()
{
	if (ChunkGenerator == NULL)
	{
		VC_ERROR("NULL chunk generator.");
	}

	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->NeedsRebuild = !ChunkGenerator->GenerateToBuffer( (VCBlock*) m_chunks[FLATTEN_WORLD(x ,y, z)]->Blocks, cX, cY, cZ );
	}}}
}

void VCWorld::Rebuild(VCWorldRebuildParams params)
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Rebuild(params);
	}}}
}

void VCWorld::SetViewDistance( int viewDistTwo )
{
	if (((viewDistTwo - 1) & viewDistTwo))
	{
		VC_ERROR("View distance must be a power of two!");
	}

	m_viewDistTwo = viewDistTwo;
	m_logViewDistTwo = std::log(m_viewDistTwo) / std::log(2);
}

VCBlock VCWorld::GetBlock ( int x, int y, int z )
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

void VCWorld::SetBlock ( int x, int y, int z, VCBlock block )
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

void VCWorld::GetWorldBounds ( glm::vec3* lower, glm::vec3* upper )
{
	lower->x = ChunkZeroX * CHUNK_WIDTH;
	lower->y = ChunkZeroY * CHUNK_WIDTH;
	lower->z = ChunkZeroZ * CHUNK_WIDTH;

	upper->x = lower->x + m_viewDistTwo * CHUNK_WIDTH;
	upper->y = lower->y + m_viewDistTwo * CHUNK_WIDTH;
	upper->z = lower->z + m_viewDistTwo * CHUNK_WIDTH;
}

bool VCWorld::RaycastWorld( Ray ray, RaycastHit* hit )
{
	glm::vec3 wLoBound, wHiBound;
	GetWorldBounds(&wLoBound, &wHiBound);

	// Normalize Direction
	ray.Direction = glm::normalize(ray.Direction);

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
	glm::vec3 face;

	// Avoids an infinite loop.
	if (dx == 0 && dy == 0 && dz == 0)
	{
		std::cout << "Attempted to ray-cast with a zero direction vector." << std::endl;
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
				face = glm::vec3(-stepX, 0, 0);
			} 

			else 
			{
				if (tMaxZ > ray.MaxDistance) 
					break;

				z += stepZ;
				tMaxZ += tDeltaZ;
				face = glm::vec3(0, 0, -stepZ);
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
				face = glm::vec3(0, -stepY, 0);
			} 

			else 
			{
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
				if (tMaxZ > ray.MaxDistance) 
					break;

				z += stepZ;
				tMaxZ += tDeltaZ;
				face = glm::vec3(0, 0, -stepZ);
			}
		}
	}

	return false;
}

// =====   Serialize   ======================================================
void VCWorld::Save( std::ofstream& stream )
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Save(stream);
	}}}
}

void VCWorld::Load( std::ifstream& stream )
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Load(stream);
	}}}
}

// =====   Interop   ======================================================
void VCWorld::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("World::VCInteropNewWorld",					(void*)VCInteropNewWorld);
	VCMonoRuntime::SetMethod("World::VCInteropReleaseWorld",				(void*)VCInteropReleaseWorld);

	VCMonoRuntime::SetMethod("World::VCInteropWorldGetBlock",				(void*)VCInteropWorldGetBlock);
	VCMonoRuntime::SetMethod("World::VCInteropWorldSetBlock",				(void*)VCInteropWorldSetBlock);
	VCMonoRuntime::SetMethod("World::VCInteropWorldSetGenerator",			(void*)VCInteropWorldSetGenerator);
	VCMonoRuntime::SetMethod("World::VCInteropWorldSetViewDist",			(void*)VCInteropWorldSetViewDist);
	VCMonoRuntime::SetMethod("World::VCInteropWorldInitializeEmpty",		(void*)VCInteropWorldInitializeEmpty);

	VCMonoRuntime::SetMethod("World::VCInteropWorldSaveToFile",				(void*)VCInteropWorldSaveToFile);
	VCMonoRuntime::SetMethod("World::VCInteropWorldLoadFromFile",			(void*)VCInteropWorldLoadFromFile);
	
	VCMonoRuntime::SetMethod("World::VCInteropWorldGenerateRegenerate",		(void*)VCInteropWorldGenerateRegenerate);
	VCMonoRuntime::SetMethod("World::VCInteropWorldRebuild",				(void*)VCInteropWorldRebuild);
	VCMonoRuntime::SetMethod("World::VCInteropWorldRaycast",				(void*)VCInteropWorldRaycast);
}

int VCInteropNewWorld()
{
	VCWorld* world = new VCWorld();
	return world->Handle;
}

void VCInteropReleaseWorld( int handle )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropWorldSetGenerator( int wHandle, int cHandle )
{
	VCWorld* wObj = (VCWorld*) VCObjectStore::Instance->GetObject(wHandle);
	VCIChunkGenerator* cObj = (VCIChunkGenerator*) VCObjectStore::Instance->GetObject(cHandle);

	wObj->ChunkGenerator = cObj;
}

void VCInteropWorldSetViewDist( int handle, int distance )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->SetViewDistance(distance);
}

void VCInteropWorldInitializeEmpty( int handle )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->InitializeEmpty();
}

void VCInteropWorldGenerateRegenerate( int handle )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->GenerateRegenerate();
}

void VCInteropWorldRebuild( int handle, VCWorldRebuildParams params )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->Rebuild(params);
}

void VCInteropWorldSaveToFile( int handle, VCMonoStringPtr path )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);

	{
		std::ofstream ofs((char*)VCMonoString(path), std::ios::in | std::ios::binary);
		obj->Save(ofs);
	}

}

void VCInteropWorldLoadFromFile( int handle, VCMonoStringPtr path )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);

	{
		std::ifstream ifs((char*)VCMonoString(path), std::ios::out | std::ios::binary);
		obj->Load(ifs);
	}

}


VCInteropBlock VCInteropWorldGetBlock( int handle, int x, int y, int z )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	return obj->GetBlock(x, y, z).AsInterop();
}

void VCInteropWorldSetBlock( int handle, int x, int y, int z, VCInteropBlock block )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->SetBlock(x, y, z, VCBlock(block));
}

int VCInteropWorldRaycast(int handle, Ray ray, RaycastHit* hitOut )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	return obj->RaycastWorld(ray, hitOut);
}