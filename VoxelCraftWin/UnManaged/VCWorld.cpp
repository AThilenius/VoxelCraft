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
#include "StreamHelpers.h"

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

void VCWorld::Rebuild()
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Rebuild();
	}}}
}

bool VCWorld::RaycastWorld( Ray ray, RaycastHit* hit )
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

// =====   Serialize   ======================================================
void VCWorld::Save( ofstream& stream )
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Save(stream);
	}}}
}

void VCWorld::Load( ifstream& stream )
{
	WORLD_ORDERED_ITTORATOR(cX, cY, cZ)
		m_chunks[FLATTEN_WORLD(x ,y, z)]->Load(stream);
	}}}
}

// =====   Interop   ======================================================
void VCWorld::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.World::VCInteropNewWorld",					(void*)VCInteropNewWorld);
	mono_add_internal_call("VCEngine.World::VCInteropReleaseWorld",				(void*)VCInteropReleaseWorld);

	mono_add_internal_call("VCEngine.World::VCInteropWorldGetBlock",			(void*)VCInteropWorldGetBlock);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetBlock",			(void*)VCInteropWorldSetBlock);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetGenerator",		(void*)VCInteropWorldSetGenerator);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetViewDist",			(void*)VCInteropWorldSetViewDist);
	mono_add_internal_call("VCEngine.World::VCInteropWorldInitializeEmpty",		(void*)VCInteropWorldInitializeEmpty);

	mono_add_internal_call("VCEngine.World::VCInteropWorldSaveToFile",			(void*)VCInteropWorldSaveToFile);
	mono_add_internal_call("VCEngine.World::VCInteropWorldLoadFromFile",		(void*)VCInteropWorldLoadFromFile);

	mono_add_internal_call("VCEngine.World::VCInteropWorldGenerateRegenerate",	(void*)VCInteropWorldGenerateRegenerate);
	mono_add_internal_call("VCEngine.World::VCInteropWorldRebuild",				(void*)VCInteropWorldRebuild);
	mono_add_internal_call("VCEngine.World::VCInteropWorldRaycast",				(void*)VCInteropWorldRaycast);
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

void VCInteropWorldRebuild( int handle )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->Rebuild();
}


void VCInteropWorldSaveToFile( int handle, MonoString* path )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	char* p = mono_string_to_utf8(path);

	{
		std::ofstream ofs(p, ios::in | ios::binary);
		obj->Save(ofs);
	}

	mono_free(p);
}

void VCInteropWorldLoadFromFile( int handle, MonoString* path )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	char* p = mono_string_to_utf8(path);

	{
		std::ifstream ifs(p, ios::out | ios::binary);
		obj->Load(ifs);
	}

	mono_free(p);
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