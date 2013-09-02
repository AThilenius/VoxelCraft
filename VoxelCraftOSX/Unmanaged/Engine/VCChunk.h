//
//  VCChunk.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#import "PCH.h"
#import "VCGameObject.h"
#import "VCWorld.h"
#import "VCBlock.h"
#import "VCChunkGenerator.h"

using namespace std;

struct BlockVerticie
{
	BlockVerticie() {}
	BlockVerticie(GLbyte3 position, GLbyte normal, GLubyte4 color )
	{
		this->position = position;
		this->normal = normal;
		this->color = color;
	}

	GLbyte3  position;
	GLbyte	 normal;
	GLubyte4 color;
};

class VCChunk : public VCGameObject
{
public:
	VCChunk(int x, int y, int z, VCWorld* world);
	~VCChunk(void);

	BlockType GetBlock ( int x, int y, int z );

	void Generate( );
	void StartRebuild ( );
	void ContinueRebuild ( double allocatedTime );
	
    void virtual Render();

private:
	BlockType m_blocks[CHUNK_TOTAL_COUNT];
	VCWorld* m_world;
	VCChunkGenerator* m_chunkGenertor;

	int m_x;
	int m_y;
	int m_z;

	// Rendering
    GLuint m_vaoID;
	GLuint m_vertexBufferID;
	GLint m_vertexCount;
	
	// Used for cross frame rebuilding.
	int m_rbZ;
	double m_rebuildStartTime;
	double m_remainingRebuildTime;

	//std::vector<BlockVerticie> m_rebuildVerticies;
	BlockVerticie* m_rebuildVerticies;

};

