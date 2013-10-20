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
#include "VCIRenderable.h"

class VCWorld;
class VCRenderState;

using namespace std;

struct BlockVerticie
{
	BlockVerticie() {}
	BlockVerticie(GLbyte3 position, GLbyte normal, GLubyte4 color ) : position(position), normal(normal), color(color){}

	GLbyte3  position;
	GLbyte	 normal;
	GLubyte4 color;
};

struct VCRunLengtth
{
	VCRunLengtth(): Color(0, 0, 0, 0), Length(0){}
	GLubyte4 Color;
	unsigned int Length;
};

class VCChunk : public VCGameObject, public VCIRenderable
{
public:
	VCChunk();
	VCChunk(int x, int y, int z, VCWorld* world);
	~VCChunk(void);

	void Initialize();

	VCBlock GetBlock ( int x, int y, int z )
	{
		if ( x < 0 || y < 0 || z < 0 ||  x >= CHUNK_WIDTH || y >= CHUNK_WIDTH || z >= CHUNK_WIDTH )
			return VCBlock::ErrorBlock;

		return Blocks[FLATTEN_CHUNK(x,y,z)];
	}
	
	void SetBlock( int x, int y, int z, VCBlock block )
	{
		if ( x < 0 || y < 0 || z < 0 ||  x >= CHUNK_WIDTH || y >= CHUNK_WIDTH || z >= CHUNK_WIDTH )
			return;

		Blocks[FLATTEN_CHUNK(x,y,z)] = block;
		NeedsRebuild = true;
	}

	void Rebuild ( );
	VCBlock Blocks[CHUNK_TOTAL_COUNT];
	bool NeedsRebuild;

	// ===== Serialization ======================================================
	void Save (ofstream& stream);
	void Load (ifstream& stream);

	// ===== Render State Fulfillment ===========================================
	virtual VCRenderState* GetState() { return VCChunk::VoxelRenderState; }
    void virtual Render();
	static VCRenderState* VoxelRenderState;

private:
	VCWorld* m_world;

	int m_x, m_y, m_z;
	int m_blockX, m_blockY, m_blockZ;
	bool m_isEmpty;
	bool m_isRegistered;

	// Rendering
    GLuint m_VAO;
	GLuint m_VBO;
	GLint m_vertexCount;

	BlockVerticie* m_rebuildVerticies;

	friend class VCChunkGenerator;
};