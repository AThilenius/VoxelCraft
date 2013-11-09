//
//  VCChunk.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCChunk.h"

#include "Shader.h"
#include "VCShadowShader.h"
#include "VCVoxelShader.h"
#include "VCWorld.h"
#include "VCGLRenderer.h"
#include "VCTime.h"

VCRenderState* VCChunk::VoxelRenderState = NULL;

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
	if (VCChunk::VoxelRenderState == NULL)
	{
		
		VCChunk::VoxelRenderState = new VCRenderState(2);

		// Stage 1
		VCChunk::VoxelRenderState->Stages[0].FrameBuffer = VCGLRenderer::Instance->DepthFrameBuffer;
		VCChunk::VoxelRenderState->Stages[0].Shader = VCGLRenderer::Instance->ShadowShader;

		// Stage 2
		VCChunk::VoxelRenderState->Stages[1].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
		VCChunk::VoxelRenderState->Stages[1].Shader = VCGLRenderer::Instance->VoxelShader;
		VCChunk::VoxelRenderState->Stages[1].Textures.push_back(VCGLRenderer::Instance->DepthTexture);
		
		VCGLRenderer::Instance->RegisterState(VoxelRenderState);
	}
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
#define OccusionValue 3
void Occlude ( GLubyte4& c )
{
	c = c + GLubyte4 ( OccusionValue, OccusionValue, OccusionValue, 0 );
}

void VCChunk::Rebuild()
{
	if (!NeedsRebuild)
		return;

	NeedsRebuild = false;
	m_vertexCount = 0;
	float startTime = VCTime::CurrentTime;

	m_rebuildVerticies = (BlockVerticie*) malloc(sizeof(BlockVerticie) * 18 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH);

    // Metrics
    int airBlocks = 0;
	int runCount = 0;

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
                
				GLbyte normal;
                
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

				// Color Corrections
				GLubyte4 V1C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V2C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V3C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V4C ( 10, 10, 10, thisType.Color.w );

				GLubyte4 V5C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V6C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V7C ( 10, 10, 10, thisType.Color.w );
				GLubyte4 V8C ( 10, 10, 10, thisType.Color.w );

				// =====   Color Corrections Computations   ======================================================

				// Upper ( +Y )
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z	 ).IsTranslucent() ) { Occlude(V3C); Occlude(V7C); }
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V3C); }
				if ( !m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V3C); Occlude(V4C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V4C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z	 ).IsTranslucent() ) { Occlude(V4C); Occlude(V8C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y + 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V8C); }
				if ( !m_world->GetBlock(m_blockX + x,		m_blockY + y + 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V7C); Occlude(V8C); }
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y + 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V7C); }

				// lOWWER ( -Y )
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z	 ).IsTranslucent() ) { Occlude(V2C); Occlude(V6C); }
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V2C); }
				if ( !m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V1C); Occlude(V2C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z + 1 ).IsTranslucent() ) { Occlude(V1C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z	 ).IsTranslucent() ) { Occlude(V1C); Occlude(V5C); }
				if ( !m_world->GetBlock(m_blockX + x - 1,	m_blockY + y - 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V5C); }
				if ( !m_world->GetBlock(m_blockX + x,		m_blockY + y - 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V5C); Occlude(V6C); }
				if ( !m_world->GetBlock(m_blockX + x + 1,	m_blockY + y - 1,	m_blockZ + z - 1 ).IsTranslucent() ) { Occlude(V6C); }

				V1C = thisType.Color * glm::vec4 ( 10.0f / V1C.x, 10.0f / V1C.y, 10.0f / V1C.z, 1.0f );
				V2C = thisType.Color * glm::vec4 ( 10.0f / V2C.x, 10.0f / V2C.y, 10.0f / V2C.z, 1.0f );
				V3C = thisType.Color * glm::vec4 ( 10.0f / V3C.x, 10.0f / V3C.y, 10.0f / V3C.z, 1.0f );
				V4C = thisType.Color * glm::vec4 ( 10.0f / V4C.x, 10.0f / V4C.y, 10.0f / V4C.z, 1.0f );
				V5C = thisType.Color * glm::vec4 ( 10.0f / V5C.x, 10.0f / V5C.y, 10.0f / V5C.z, 1.0f );
				V6C = thisType.Color * glm::vec4 ( 10.0f / V6C.x, 10.0f / V6C.y, 10.0f / V6C.z, 1.0f );
				V7C = thisType.Color * glm::vec4 ( 10.0f / V7C.x, 10.0f / V7C.y, 10.0f / V7C.z, 1.0f );
				V8C = thisType.Color * glm::vec4 ( 10.0f / V8C.x, 10.0f / V8C.y, 10.0f / V8C.z, 1.0f );

				// =====   Verticie Computations   ======================================================

                // Front face
                if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1).IsTranslucent() )
                {
                    normal = 5;
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, V1C ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, V3C ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, V4C ));
                    
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, V1C ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, V2C ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, V3C ));
                }

				//Right face
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 1;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, V2C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, V7C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, V3C ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, V2C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, V6C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, V7C ));
				}

				//Back face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1).IsTranslucent() )
				{
					normal = 4;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, V6C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, V8C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, V7C ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, V6C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, V5C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, V8C ));
				}

				//Left face
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 0;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, V5C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, V4C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, V8C ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, V5C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, V1C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, V4C ));
				}

				//Top face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 3;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, V4C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, V3C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, V7C ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, V4C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, V7C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, V8C ));
				}

				//Bottom face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 2;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color  - V1C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color  - V1C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, thisType.Color  - V1C ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color  - V1C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, thisType.Color  - V1C ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color  - V1C ));
				}
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
	}

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	//std::std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - startTime) << " seconds." << std::endl;
    
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