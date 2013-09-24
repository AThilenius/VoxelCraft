//
//  VCWorld.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define FLATTEN_WORLD(X,Y,Z) ((((Z << m_logViewDist) + X) << m_logViewDist ) + Y)
#define WORLD_ORDERED_ITTORATOR(xName,yName,zName) for ( int zName = 0; zName < m_viewDist * 2; zName++ ){ for ( int xName = 0; xName < m_viewDist * 2; xName++ ){ for ( int yName = 0; yName < m_viewDist * 2; yName++ ) {

#include "VCBlock.h"
class VCChunk;

class VCWorld
{
public:
	VCWorld(int viewDistance);
	~VCWorld(void);

	void Initialize();
	BlockType GetBlock ( int x, int y, int z );

private:
	int m_viewDist;
	int m_logViewDist;
	int m_c0x, m_c0y, m_c0z;
	VCChunk** m_chunks;

};

