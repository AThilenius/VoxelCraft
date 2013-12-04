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
#include "VCRenderStage.h"
#include "VCShader.h"
#include "VCVoxelFallbackShader.h"

struct BlockVerticie
{
	BlockVerticie() {}
	BlockVerticie(GLbyte3 position, GLbyte normal, GLubyte4 color ) : position(position), normal(normal), color(color){}

	GLbyte3  position;
	GLbyte	 normal;
	GLubyte4 color;
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
	m_isEmpty(true),
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
	m_isEmpty(true),
	NeedsRebuild(true)
{
}

VCChunk::~VCChunk(void)
{
	VCGLRenderer::Instance->UnRegisterStage(m_renderStage);

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		m_VAO = 0;
	}
}

void VCChunk::Initialize()
{
	// =====   Render Stages   ======================================================
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VCChunk, &VCChunk::Render>(this));
	m_renderStage->Camera = m_world->Camera;
	m_renderStage->Shader = VCGLRenderer::Instance->VoxelFallbackShader;
	m_renderStage->ExectionType = VCRenderStage::Never;
	VCGLRenderer::Instance->RegisterStage(m_renderStage);

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
	glEnableVertexAttribArray(VC_ATTRIBUTE_NORMAL);
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_BYTE,			GL_FALSE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, position) );
	glVertexAttribIPointer(VC_ATTRIBUTE_NORMAL,		1,	GL_BYTE,						sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, normal) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, color) );

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
#define Occlude(val) val += 0.2f

void VCChunk::Rebuild(VCWorldRebuildParams params)
{
	if (!NeedsRebuild && !params.ForceRebuildAll)
		return;

	NeedsRebuild = false;
	m_vertexCount = 0;
	float startTime = VCTime::CurrentTime;

	BlockVerticie* m_rebuildVerticies = (BlockVerticie*) malloc(sizeof(BlockVerticie) * 18 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH);

	// Metrics
	int airBlocks = 0;
	int runCount = 0;

	// =====   Per-Iteration Variables   ======================================================

	GLbyte normal;

	// Color Corrections
	float V1C;
	float V2C;
	float V3C;
	float V4C;

	float V5C;
	float V6C;
	float V7C;
	float V8C;

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

				GLbyte xO = x;
				GLbyte yO = y;
				GLbyte zO = z;

				// Verts
				GLbyte3 V1 ( xO,		yO,		zO + 1	);
				GLbyte3 V2 ( xO + 1,	yO,		zO + 1	);
				GLbyte3 V3 ( xO + 1,	yO + 1, zO + 1	);
				GLbyte3 V4 ( xO,		yO + 1, zO + 1	);

				GLbyte3 V5 ( xO,		yO,		zO		);
				GLbyte3 V6 ( xO + 1,	yO,		zO		);
				GLbyte3 V7 ( xO + 1,	yO + 1, zO		);
				GLbyte3 V8 ( xO,		yO + 1, zO		);

				GLubyte4 black ( 0, 0, 0, thisType.Color.w );

				// =====   Verticie Computations   ======================================================

				// Front face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1).IsTranslucent() )
				{
					normal = 5;

					V1C = V2C = V3C = V4C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V1C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y,		m_blockZ + z + 1).IsSolid()) { Occlude(V1C); Occlude(V4C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V4C); }

						if (m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V1C); Occlude(V2C); }
						if (m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V3C); Occlude(V4C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V2C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y,		m_blockZ + z + 1).IsSolid()) { Occlude(V2C); Occlude(V3C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V3C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, GLubyte4::Lerp(thisType.Color, black, V1C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, GLubyte4::Lerp(thisType.Color, black, V3C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, GLubyte4::Lerp(thisType.Color, black, V4C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, GLubyte4::Lerp(thisType.Color, black, V1C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, GLubyte4::Lerp(thisType.Color, black, V2C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, GLubyte4::Lerp(thisType.Color, black, V3C) ));
				}

				//Back face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1).IsTranslucent() )
				{
					normal = 4;

					V5C = V6C = V7C = V8C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V5C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y,		m_blockZ + z - 1).IsSolid()) { Occlude(V5C); Occlude(V8C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V8C); }

						if (m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V5C); Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V7C); Occlude(V8C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y,		m_blockZ + z - 1).IsSolid()) { Occlude(V6C); Occlude(V7C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V7C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, GLubyte4::Lerp(thisType.Color, black, V6C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, GLubyte4::Lerp(thisType.Color, black, V8C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, GLubyte4::Lerp(thisType.Color, black, V7C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, GLubyte4::Lerp(thisType.Color, black, V6C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, GLubyte4::Lerp(thisType.Color, black, V5C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, GLubyte4::Lerp(thisType.Color, black, V8C) ));
				}

				//Right face
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 1;

					V2C = V3C = V6C = V7C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y,		m_blockZ + z - 1).IsSolid()) { Occlude(V6C); Occlude(V7C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V7C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z	).IsSolid()) { Occlude(V2C); Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z	).IsSolid()) { Occlude(V3C); Occlude(V7C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V2C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y,		m_blockZ + z + 1).IsSolid()) { Occlude(V2C); Occlude(V3C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V3C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, GLubyte4::Lerp(thisType.Color, black, V2C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, GLubyte4::Lerp(thisType.Color, black, V7C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, GLubyte4::Lerp(thisType.Color, black, V3C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, GLubyte4::Lerp(thisType.Color, black, V2C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, GLubyte4::Lerp(thisType.Color, black, V6C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, GLubyte4::Lerp(thisType.Color, black, V7C) ));
				}

				//Left face
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 0;

					V1C = V4C = V5C = V8C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V5C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y,		m_blockZ + z - 1).IsSolid()) { Occlude(V5C); Occlude(V8C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V8C); }

						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z	).IsSolid()) { Occlude(V1C); Occlude(V5C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z	).IsSolid()) { Occlude(V4C); Occlude(V8C); }

						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V1C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y,		m_blockZ + z + 1).IsSolid()) { Occlude(V1C); Occlude(V4C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V4C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, GLubyte4::Lerp(thisType.Color, black, V5C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, GLubyte4::Lerp(thisType.Color, black, V4C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, GLubyte4::Lerp(thisType.Color, black, V8C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, GLubyte4::Lerp(thisType.Color, black, V5C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, GLubyte4::Lerp(thisType.Color, black, V1C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, GLubyte4::Lerp(thisType.Color, black, V4C) ));
				}

				//Top face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 3;

					V3C = V4C = V7C = V8C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V8C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z	).IsSolid()) { Occlude(V8C); Occlude(V4C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V4C); }

						if (m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V7C); Occlude(V8C); }
						if (m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V3C); Occlude(V4C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V7C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z	).IsSolid()) { Occlude(V7C); Occlude(V3C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V3C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, GLubyte4::Lerp(thisType.Color, black, V4C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, GLubyte4::Lerp(thisType.Color, black, V3C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, GLubyte4::Lerp(thisType.Color, black, V7C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, GLubyte4::Lerp(thisType.Color, black, V4C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, GLubyte4::Lerp(thisType.Color, black, V7C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, GLubyte4::Lerp(thisType.Color, black, V8C) ));
				}

				//Bottom face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 2;

					V1C = V2C = V5C = V6C = 0.0f;

					if (params.ShowShadows)
					{
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V5C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z	).IsSolid()) { Occlude(V4C); Occlude(V1C); }
						if (m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V1C); }

						if (m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V5C); Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V1C); Occlude(V2C); }

						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z - 1).IsSolid()) { Occlude(V6C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z	).IsSolid()) { Occlude(V6C); Occlude(V2C); }
						if (m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z + 1).IsSolid()) { Occlude(V2C); }
					}

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, GLubyte4::Lerp(thisType.Color, black, V1C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, GLubyte4::Lerp(thisType.Color, black, V6C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, GLubyte4::Lerp(thisType.Color, black, V2C) ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, GLubyte4::Lerp(thisType.Color, black, V1C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, GLubyte4::Lerp(thisType.Color, black, V5C) ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, GLubyte4::Lerp(thisType.Color, black, V6C) ));
				}
				// =========  END of make block  ========
			}
		}
	}

	// Empty?
	m_isEmpty = m_vertexCount == 0;
	if (m_isEmpty)
		m_renderStage->ExectionType = VCRenderStage::Never;

	else
	{
		// Update VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(BlockVerticie) * m_vertexCount, &m_rebuildVerticies[0] , GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_renderStage->ExectionType = VCRenderStage::Always;
	}

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	glErrorCheck();
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

	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

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