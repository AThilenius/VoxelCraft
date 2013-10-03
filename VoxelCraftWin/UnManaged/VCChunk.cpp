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
    m_vertexBufferID(0),
    m_vertexCount(0),
    m_vaoID(0),
    m_rebuildVerticies(NULL)
{
	if (VCChunk::VoxelRenderState == NULL)
	{
		VCChunk::VoxelRenderState = new VCRenderState();
		VCChunk::VoxelRenderState->StageCount = 2;

		// Stage 1
		VCChunk::VoxelRenderState->Stages[0].FrameBuffer = VCGLRenderer::Instance->DepthFrameBuffer;
		VCChunk::VoxelRenderState->Stages[0].Shader = VCGLRenderer::Instance->ShadowShader;

		// Stage 2
		VCChunk::VoxelRenderState->Stages[1].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
		VCChunk::VoxelRenderState->Stages[1].Shader = VCGLRenderer::Instance->VoxelShader;
		VCChunk::VoxelRenderState->Stages[1].Viewport = RectangleF(0, 0, 0.8f, 0.9f);
		VCChunk::VoxelRenderState->Stages[1].Textures[0] = VCGLRenderer::Instance->DepthTexture;

		VCGLRenderer::Instance->RegisterState(VoxelRenderState);
	}

    //cout << "VCChunk created [ " << x << " : " << y << " : " << z << " ] with handle: " << Handle << endl;
	m_chunkGenertor = new VCChunkGenerator(x, y, z);
}

VCChunk::~VCChunk(void)
{
	delete m_chunkGenertor;
}

BlockType VCChunk::GetBlock ( int x, int y, int z )
{
	if ( x < 0 || y < 0 || z < 0 ||  x >= CHUNK_WIDTH || y >= CHUNK_WIDTH || z >= CHUNK_WIDTH )
		return Block_Unknown;
    
    return m_blocks[FLATTEN_CHUNK(x,y,z)];
}

void VCChunk::Generate()
{
	//for (int i = 0; i < CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH; i++ )
	//	m_blocks[i] = Block_Dirt;

	m_chunkGenertor->generateToBuffer((byte*)m_blocks);
}

void VCChunk::Rebuild()
{
	m_vertexCount = 0;
	float startTime = VCTime::CurrentTime;

	// Alloc worst case for rebuild
	if ( m_rebuildVerticies != NULL )
		free(m_rebuildVerticies);

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

                BlockType thisType = m_blocks[FLATTEN_CHUNK(x,y,z)];
				GLubyte4 color = GLubyte4( 255, 0, 0, 255 );

				if ( thisType == Block_Air )
                {
                    airBlocks++;
                    continue;
                }

				if ( thisType == Block_Dirt )
					color = GLubyte4(92, 86, 37, 255);

				else if ( thisType == Block_Grass )
					color = GLubyte4(110, 163, 40, 255);

				else if ( thisType == Block_Stone )
					color = GLubyte4(128, 128, 128, 255);
                
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
                

                BlockType blockType = Block_Unknown;
                
                // Front face
				blockType = m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1);
                if ( blockType == Block_Air || blockType == Block_Unknown )
                {
                    normal = 5;
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, color ));
                    
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, color ));
                    m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, color ));
                }

				//Right face
				blockType = m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z);
				if ( blockType == Block_Air || blockType == Block_Unknown )
				{
					normal = 1;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, color ));
				}

				//Back face
				blockType = m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1);
				if ( blockType == Block_Air || blockType == Block_Unknown )
				{
					normal = 4;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, color ));
				}

				//Left face
				blockType = m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z);
				if ( blockType == Block_Air || blockType == Block_Unknown )
				{
					normal = 0;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, color ));
				}

				//Top face
				blockType = m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z);
				if ( blockType == Block_Air || blockType == Block_Unknown )
				{
					normal = 3;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V3, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V4, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V7, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V8, normal, color ));
				}

				//Bottom face
				blockType = m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z);
				if ( blockType == Block_Air || blockType == Block_Unknown )
				{
					normal = 2;
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V2, normal, color ));

					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V1, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V5, normal, color ));
					m_rebuildVerticies[m_vertexCount++] = ( BlockVerticie( V6, normal, color ));
				}
                // =========  END of make block  ========
            }
        }
    }

	if(m_vertexBufferID != 0)
	{
		glDeleteBuffers(1, &m_vertexBufferID);
		m_vertexBufferID = 0;
	}

    
    // Create VAO
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);
    glErrorCheck();
    
    // Create VBO
    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	ZERO_CHECK(m_vertexBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(BlockVerticie) * m_vertexCount, &m_rebuildVerticies[0] , GL_STATIC_DRAW);
    
    // Bind Attributes
    glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glEnableVertexAttribArray(VC_ATTRIBUTE_NORMAL);
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
    
	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_BYTE,			GL_FALSE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, position) );
	glVertexAttribIPointer(VC_ATTRIBUTE_NORMAL,		1,	GL_BYTE,						sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, normal) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(BlockVerticie),	(void*) offsetof(BlockVerticie, color) );
    
    glBindVertexArray(0);

	// Register VCIRenderable
	VCGLRenderer::Instance->RegisterIRenderable(this);

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - startTime) << " seconds." << endl;
    
	glErrorCheck();
}

void VCChunk::Render()
{
	if (m_vertexBufferID == 0 )
		return;
    
    glBindVertexArray(m_vaoID);
	VCGLRenderer::Instance->SetModelMatrix(glm::translate(
		(float)m_x * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_y * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_z * BLOCK_RENDER_SIZE * CHUNK_WIDTH));

	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    
    glBindVertexArray(0);
	glErrorCheck();
}