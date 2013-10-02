//
//  VCChunk.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCGameObject.h"
#include "VCBlock.h"
#include "VCChunkGenerator.h"

class VCWorld;
class VCRenderState;

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
	void Rebuild ( );
	
    void virtual Render();
	static VCRenderState* VoxelRenderState;

private:
	BlockType m_blocks[CHUNK_TOTAL_COUNT];
	VCWorld* m_world;
	VCChunkGenerator* m_chunkGenertor;

	int m_x, m_y, m_z;
	int m_blockX, m_blockY, m_blockZ;

	// Rendering
    GLuint m_vaoID;
	GLuint m_vertexBufferID;
	GLint m_vertexCount;

	//std::vector<BlockVerticie> m_rebuildVerticies;
	BlockVerticie* m_rebuildVerticies;

};

