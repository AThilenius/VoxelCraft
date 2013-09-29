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

VCWorld::VCWorld( int viewDistance )
{
	if (((viewDistance - 1) & viewDistance))
		cout << "View distance must be a power of two!" << endl;

	m_viewDistTwo = viewDistance;
	m_logViewDistTwo = std::log(m_viewDistTwo) / std::log(2);

	m_c0x = m_c0y = m_c0z = 0;
}

VCWorld::~VCWorld(void)
{
}

void VCWorld::Initialize()
{
	m_chunks = (VCChunk**) malloc ( sizeof(VCChunk*) * m_viewDistTwo * m_viewDistTwo * m_viewDistTwo );
	
	m_c0x = 0;
	m_c0y = 0;
	m_c0z = 0;

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)] = new VCChunk(X, Y, Z, this);
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->SetParent(VCSceneGraph::Instance->RootNode);
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->Generate();
	}}};

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->Rebuild();
	}}};

}
