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

VCWorld* VCWorld::Instance;

VCWorld::VCWorld( int viewDistance ):
	ChunkZeroX(0),
	ChunkZeroY(0),
	ChunkZeroZ(0)
{
	VCWorld::Instance = this;

	if (((viewDistance - 1) & viewDistance))
		cout << "View distance must be a power of two!" << endl;

	m_viewDistTwo = viewDistance;
	m_logViewDistTwo = std::log(m_viewDistTwo) / std::log(2);
}

VCWorld::~VCWorld(void)
{
}

void VCWorld::Initialize()
{
	m_chunks = (VCChunk**) malloc ( sizeof(VCChunk*) * m_viewDistTwo * m_viewDistTwo * m_viewDistTwo );

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)] = new VCChunk(X, Y, Z, this);
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->SetParent(VCSceneGraph::Instance->RootNode);
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->Generate();
	}}};

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->Rebuild();
	}}};

}

void VCWorld::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.World::VCInteropWorldGetBlock", (void*)VCInteropWorldGetBlock);
}

int VCInteropWorldGetBlock( int x, int y, int z )
{
	return VCWorld::Instance->GetBlock(x, y, z);
}
