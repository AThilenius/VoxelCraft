//
//  VCChunk.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCWorld.h"
#include "VCChunk.h"
#include "VCGLRenderer.h"

VCRenderState* VCChunk::VoxelRenderState = NULL;

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
		
		VCChunk::VoxelRenderState = new VCRenderState();

		//// Shadows supported?
		//if (VCGLRenderer::Instance->DepthTexture != NULL)
		//{
			VCChunk::VoxelRenderState->StageCount = 2;

			// Stage 1
			VCChunk::VoxelRenderState->Stages[0].FrameBuffer = VCGLRenderer::Instance->DepthFrameBuffer;
			VCChunk::VoxelRenderState->Stages[0].Shader = VCGLRenderer::Instance->ShadowShader;

			// Stage 2
			VCChunk::VoxelRenderState->Stages[1].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
			VCChunk::VoxelRenderState->Stages[1].Shader = VCGLRenderer::Instance->VoxelShader;
			VCChunk::VoxelRenderState->Stages[1].Textures[0] = VCGLRenderer::Instance->DepthTexture;
		//}

		//else
		//{
		//	VCChunk::VoxelRenderState->StageCount = 1;

		//	// Stage 1
		//	VCChunk::VoxelRenderState->Stages[1].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
		//	VCChunk::VoxelRenderState->Stages[1].Shader = VCGLRenderer::Instance->VoxelShader;
		//}
		

		VCGLRenderer::Instance->RegisterState(VoxelRenderState);
	}
}

VCChunk::~VCChunk(void)
{
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
                
                //GLKVector3 normal;
				GLbyte normal;
                
                GLbyte xO = x;
                GLbyte yO = y;
                GLbyte zO = z;
                
				GLbyte3 V1 ( xO,		yO,		zO + 1	);
                GLbyte3 V2 ( xO + 1,	yO,		zO + 1	);
                GLbyte3 V3 ( xO + 1,	yO + 1, zO + 1	);
                GLbyte3 V4 ( xO,		yO + 1, zO + 1	);
                
                GLbyte3 V5 ( xO,		yO,		zO		);
                GLbyte3 V6 ( xO + 1,	yO,		zO		);
                GLbyte3 V7 ( xO + 1,	yO + 1, zO		);
                GLbyte3 V8 ( xO,		yO + 1, zO		);

                
                // Front face
                if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1).IsTranslucent() )
                {
                    normal = 5;
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, thisType.Color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, thisType.Color ));
                    
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, thisType.Color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, thisType.Color ));
                }

				//Right face
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 1;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, thisType.Color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, thisType.Color ));
				}

				//Back face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1).IsTranslucent() )
				{
					normal = 4;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, thisType.Color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, thisType.Color ));
				}

				//Left face
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z).IsTranslucent() )
				{
					normal = 0;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, thisType.Color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, thisType.Color ));
				}

				//Top face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 3;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, thisType.Color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, thisType.Color ));
				}

				//Bottom face
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z).IsTranslucent() )
				{
					normal = 2;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, thisType.Color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, thisType.Color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, thisType.Color ));
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

	//std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - startTime) << " seconds." << endl;
    
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