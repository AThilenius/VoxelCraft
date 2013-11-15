//
//  VCChunk.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCChunk.h"

#include "VCWorld.h"
#include "VCGLRenderer.h"
#include "VCTime.h"
#include "VCCamera.h"

struct BlockVerticie
{
	BlockVerticie() {}
	BlockVerticie(GLubyte3 position, GLubyte3 color, GLushort flags ) : 
		Position(position), 
		Color(color),
		Flags(flags)
	{
	}

	GLubyte3 Position;
	GLubyte3 Color;
	GLushort Flags;
};

struct VCRunLengtth
{
	VCRunLengtth(): Color(0, 0, 0, 0), Length(0){}
	GLubyte4 Color;
	unsigned int Length;
};

VCChunk::VCChunk():
	m_x(0),
	m_y(0),
	m_z(0),
	m_blockX(0),
	m_blockY(0),
	m_blockZ(0),
	m_world(NULL),
	m_VBO(0),
	m_vertexCount(0),
	m_VAO(0),
	m_rebuildVerticies(NULL),
	m_isEmpty(true),
	m_isRegistered(false),
	NeedsRebuild(true)
{

}

VCChunk::VCChunk(int x, int y, int z, VCWorld* world):
	m_x(x),
	m_y(y),
	m_z(z),
	m_blockX(x * CHUNK_WIDTH),
	m_blockY(y * CHUNK_WIDTH),
	m_blockZ(z * CHUNK_WIDTH),
	m_world(world),
	m_VBO(0),
	m_vertexCount(0),
	m_VAO(0),
	m_rebuildVerticies(NULL),
	m_isEmpty(true),
	m_isRegistered(false),
	NeedsRebuild(true)
{
}

VCChunk::~VCChunk(void)
{
	if(m_isRegistered)
	{
		m_isRegistered = false;
		VCGLRenderer::Instance->UnRegisterIRenderable(this);
	}

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		m_VAO = 0;
	}
}

void VCChunk::Initialize()
{
	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	ZERO_CHECK(m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
	glEnableVertexAttribArray(VC_ATTRIBUTE_FLAGS);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_BYTE,			GL_FALSE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, Position) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		3,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, Color) );
	glVertexAttribIPointer(VC_ATTRIBUTE_FLAGS,		1,	GL_SHORT,						sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, Flags) );

	glBindVertexArray(0);
}

VCBlock VCChunk::GetBlock ( int x, int y, int z )
{
	if ( x < 0 || y < 0 || z < 0 ||  x >= CHUNK_WIDTH || y >= CHUNK_WIDTH || z >= CHUNK_WIDTH )
		return VCBlock::ErrorBlock;

	return Blocks[FLATTEN_CHUNK(x,y,z)];
}

void VCChunk::SetBlock( int x, int y, int z, VCBlock block )
{
	if ( x < 0 || y < 0 || z < 0 ||  x >= CHUNK_WIDTH || y >= CHUNK_WIDTH || z >= CHUNK_WIDTH )
		return;

	Blocks[FLATTEN_CHUNK(x,y,z)] = block;
	NeedsRebuild = true;
}

// Helper:
#define OccusionValue 20
#define Occlude(val) val += 0.3f

void VCChunk::Rebuild(VCWorldRebuildParams params)
{
	if (!NeedsRebuild && !params.ForceRebuildAll)
		return;

	NeedsRebuild = false;
	m_vertexCount = 0;
	float startTime = VCTime::CurrentTime;

	m_rebuildVerticies = (BlockVerticie*) malloc(sizeof(BlockVerticie) * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH);

	// Metrics
	int airBlocks = 0;
	int runCount = 0;
	
	// =====   Iterator   ======================================================
	for(int z = 0; z < CHUNK_WIDTH; z++ )
	{
		for(int x = 0; x < CHUNK_WIDTH; x++ )
		{
			for(int y = 0; y < CHUNK_WIDTH; y++ )
			{
				// =========  Make a single block  ========
				runCount++;

				VCBlock thisType = Blocks[FLATTEN_CHUNK(x,y,z)];

				if ( thisType.IsTrasparent() )
				{
					airBlocks++;
					continue;
				}

				// =====   Flags   ======================================================
				GLushort flags = 0;

				m_rebuildVerticies[m_vertexCount++] = BlockVerticie(GLubyte3(x, y, z), GLubyte3(thisType.Color.x, thisType.Color.y, thisType.Color.z), flags );
				// =========  END of make block  ========
			}
		}
	}

	// Empty?
	m_isEmpty = m_vertexCount == 0;
	if (m_isEmpty)
	{
		if(m_isRegistered)
		{
			m_isRegistered = false;
			VCGLRenderer::Instance->UnRegisterIRenderable(this);
		}

		// release heap malloc
		free(m_rebuildVerticies);
		m_rebuildVerticies = NULL;

		return;
	}

	// Update VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BlockVerticie) * m_vertexCount, &m_rebuildVerticies[0] , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Register VCIRenderable
	if (!m_isRegistered)
	{
		m_isRegistered = true;
		VCGLRenderer::Instance->RegisterIRenderable(this);
		std::cout << "Registering Chunk IRenderable." << std::endl;
	}

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	//std::std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - startTime) << " seconds." << std::endl;

	glErrorCheck();
}

VCRenderState* VCChunk::GetState()
{
	return m_world->RenderState;
}


void VCChunk::Render()
{
	// Shouldn't get here though
	if ( m_isEmpty )
		return;

	glBindVertexArray(m_VAO);
	VCGLRenderer::Instance->SetModelMatrix(glm::translate(
		(float)m_x * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_y * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_z * BLOCK_RENDER_SIZE * CHUNK_WIDTH));

	glDrawArrays(GL_POINTS, 0, m_vertexCount);

	glBindVertexArray(0);
	glErrorCheck();
}

// ===== Serialization ======================================================
void VCChunk::Save( std::ofstream& stream )
{
	// Run Length Encode chunk data

	int i = 0;
	int runs = 0;
	while ( i < CHUNK_TOTAL_COUNT ) // 32768
	{
		VCRunLengtth rl;
		runs++;
		rl.Length = 0;
		rl.Color = Blocks[i].Color;

		// Run the length
		while(i < CHUNK_TOTAL_COUNT && rl.Color == Blocks[i].Color)
		{
			rl.Length++;
			i++;
		}

		if (rl.Length == 0)
		{
			VC_ERROR("rl.Length == 0. HOW!!!");
		}

		stream.write((char*) &rl, sizeof(VCRunLengtth));
	}

}

void VCChunk::Load( std::ifstream& stream )
{
	// Run Length Decode data
	int i = 0;
	while ( i < CHUNK_TOTAL_COUNT )
	{
		VCRunLengtth rl;
		stream.read((char*) &rl, sizeof(VCRunLengtth));

		if (rl.Length == 0)
		{
			VC_ERROR("rl.Length == 0. HOW!!!");
		}

		for ( int o = 0; o < rl.Length; o++ )
		{
			Blocks[i] = VCBlock(rl.Color.x, rl.Color.y, rl.Color.z, rl.Color.w);
			i++;
		}
	}

	NeedsRebuild = true;
}