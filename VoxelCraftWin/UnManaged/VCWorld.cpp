//
//  VCWorld.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCWorld.h"

#include "VCChunk.h"
#include "VCBlock.h"
#include "VCSceneGraph.h"
#include "VCDebug.h"

VCWorld::VCWorld():
	ChunkZeroX(0),
	ChunkZeroY(0),
	ChunkZeroZ(0),
	ChunkGenerator(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCWorld::~VCWorld(void)
{
}

void VCWorld::Initialize()
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

void VCWorld::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.World::VCInteropNewWorld",					(void*)VCInteropNewWorld);
	mono_add_internal_call("VCEngine.World::VCInteropReleaseWorld",				(void*)VCInteropReleaseWorld);

	mono_add_internal_call("VCEngine.World::VCInteropWorldGetBlock",			(void*)VCInteropWorldGetBlock);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetBlock",			(void*)VCInteropWorldSetBlock);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetGenerator",		(void*)VCInteropWorldSetGenerator);
	mono_add_internal_call("VCEngine.World::VCInteropWorldSetViewDist",			(void*)VCInteropWorldSetViewDist);
	mono_add_internal_call("VCEngine.World::VCInteropWorldInitialize",			(void*)VCInteropWorldInitialize);
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

	wObj->SetGenerator(cObj);
}

void VCInteropWorldSetViewDist( int handle, int distance )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->SetViewDistance(distance);
}

void VCInteropWorldInitialize( int handle )
{
	VCWorld* obj = (VCWorld*) VCObjectStore::Instance->GetObject(handle);
	obj->Initialize();
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
