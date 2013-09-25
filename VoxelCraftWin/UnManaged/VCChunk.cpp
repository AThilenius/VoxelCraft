//
//  VCChunk.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCChunk.h"
#include "VCGLRenderer.h"


VCChunk::VCChunk(int x, int y, int z, VCWorld* world):
    m_x(x),
    m_y(y),
    m_z(x),
    m_world(world),
    m_vertexBufferID(0),
    m_vertexCount(0),
    m_vaoID(0),
    m_rebuildVerticies(NULL)
{
    cout << "VCChunk created with handle: " << Handle << endl;
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

void VCChunk::StartRebuild()
{
	m_rbZ = 0;
	m_vertexCount = 0;

	// Alloc worst case for rebuild ( 36 MB for 64x64x64 )
	if ( m_rebuildVerticies != NULL )
		free(m_rebuildVerticies);

	m_rebuildVerticies = (BlockVerticie*) malloc(sizeof(BlockVerticie) * 18 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH);

	m_rebuildStartTime = VCTime::CurrentTime;

	printf("VCChunk [ %i : %i ] flushed in prep for rebuild.\n", m_x, m_z);
}

void VCChunk::Generate()
{
	// Hack for now.
	for (int z = 0; z < CHUNK_WIDTH; z++ )
	{
		for (int x = 0; x < CHUNK_WIDTH; x++ )
		{
			for (int y = 0; y < CHUNK_WIDTH; y++ )
			{
				//if ( y < (int) CHUNK_WIDTH / 2 )
				m_blocks[FLATTEN_CHUNK(x, y, z)] = Block_Dirt;
				//else
				//	m_blocks[FLATTEN_CHUNK(x, y, z)] = Block_Air;
			}
		}
	}
}

void VCChunk::ContinueRebuild( double allocatedTime )
{
	printf("VCChunk [ %i : %i ] rebuild continuing...\n", m_x, m_z);
    
    // Metrics
    int airBlocks = 0;
	int runCount = 0;

    for(; m_rbZ < CHUNK_WIDTH; m_rbZ++ )
    {
		for(int x = 0; x < CHUNK_WIDTH; x++ )
		{
			for(int y = 0; y < CHUNK_WIDTH; y++ )
			{

                // =========  Make a single block  ========
                runCount++;

                BlockType thisType = m_blocks[FLATTEN_CHUNK(x,y,m_rbZ)];
				GLubyte4 color = GLubyte4( FastRandom() % 255, FastRandom() % 255, FastRandom() % 255, 255 );
                
                if ( thisType == Block_Air )
                {
                    airBlocks++;
                    continue;
                }

                //GLKVector3 normal;
				GLbyte normal;
                
                GLbyte xO = x;
                GLbyte yO = y;
                GLbyte zO = m_rbZ;
                
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
				blockType = GetBlock(x, y, m_rbZ + 1);
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
				blockType = GetBlock(x + 1, y, m_rbZ);
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
				blockType = GetBlock(x, y, m_rbZ - 1);
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
				blockType = GetBlock(x - 1, y, m_rbZ);
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
				blockType = GetBlock(x, y + 1, m_rbZ);
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
				blockType = GetBlock(x, y - 1, m_rbZ);
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

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - m_rebuildStartTime) << " seconds." << endl;
    
	glErrorCheck();
}

void VCChunk::Render()
{
	if (m_vertexBufferID == 0 )
		return;
    
    glBindVertexArray(m_vaoID);
	VCGLRenderer::VoxelShader->SetModelMatrix(glm::translate((float)m_x, (float)m_y, (float)m_z));

	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    
    glBindVertexArray(0);
	glErrorCheck();
}
