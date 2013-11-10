//
//  VCChunk.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCWorld;
class VCRenderState;
struct BlockVerticie;
struct VCWorldRebuildParams;

#include "VCGameObject.h"
#include "VCIRenderable.h"
#include "VCBlock.h"

class VCChunk : public VCGameObject, public VCIRenderable
{
public:
	VCChunk();
	VCChunk(int x, int y, int z, VCWorld* world);
	~VCChunk(void);

	void Initialize();
	void Rebuild (VCWorldRebuildParams params);

	VCBlock GetBlock ( int x, int y, int z );
	void SetBlock( int x, int y, int z, VCBlock block );
	
	// ===== Serialization ======================================================
	void Save (std::ofstream& stream);
	void Load (std::ifstream& stream);

	// ===== Render State Fulfillment ===========================================
	virtual VCRenderState* GetState() { return VCChunk::VoxelRenderState; }
	void virtual Render();
	static VCRenderState* VoxelRenderState;

public:
	VCBlock Blocks[CHUNK_TOTAL_COUNT];
	bool NeedsRebuild;

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