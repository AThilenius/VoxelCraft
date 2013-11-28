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
#include "VCTerrainConstructionShader.h"
#include "VCTerrianFeedbackShader.h"
#include "VCColorPassThroughShader.h"

struct BlockPoint
{
	BlockPoint() {}
	BlockPoint(GLubyte3 position, GLubyte3 color, GLushort flags ) : 
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
	m_inputVAO(0),
	m_inputBuffer(0),
	m_feedbackBuffer(0),
	m_transformFeedbackObject(0),
	m_feedbackVAO(0),
	m_inputVCount(0),
	m_rebuildVerticies(NULL),
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
	m_inputVAO(0),
	m_inputBuffer(0),
	m_feedbackBuffer(0),
	m_transformFeedbackObject(0),
	m_feedbackVAO(0),
	m_inputVCount(0),
	m_rebuildVerticies(NULL),
	m_isEmpty(true),
	NeedsRebuild(true)
{
}

VCChunk::~VCChunk(void)
{
	VCGLRenderer::Instance->RegisterStage(m_renderStage1);

	//if (m_stage1VAO != 0)
	//{
	//	glDeleteVertexArrays(1, &m_stage1VAO);
	//	glDeleteBuffers(1, &m_stage1VBO);
	//	m_stage1VAO = 0;
	//}
}

void VCChunk::Initialize()
{
	// =====   Render Stages   ======================================================
	VCCamera* testCam = new VCCamera();

	m_renderStage1 = new VCRenderStage(VCVoidDelegate::from_method<VCChunk, &VCChunk::RenderStage1>(this));
	//m_renderStage1->Camera = m_world->Camera;
	m_renderStage1->Camera = testCam;
	m_renderStage1->Shader = VCGLRenderer::Instance->TerrainConstructionShader;
	m_renderStage1->ExectionType = VCRenderStage::Never;
	VCGLRenderer::Instance->RegisterStage(m_renderStage1);

	m_renderStage2 = new VCRenderStage(VCVoidDelegate::from_method<VCChunk, &VCChunk::RenderStage2>(this));
	m_renderStage2->StageOrder = 1;
	//m_renderStage2->Camera = m_world->Camera;
	m_renderStage2->Camera = testCam;
	m_renderStage2->Shader = VCGLRenderer::Instance->ColorPassThroughShader;
	m_renderStage2->ExectionType = VCRenderStage::Never;
	VCGLRenderer::Instance->RegisterStage(m_renderStage2);

	// DEBUG
	glGenQueries(1, &m_quary);

	// =====   Input Buffer   ======================================================

	// Input VAO
	glGenVertexArrays(1, &m_inputVAO);
	glBindVertexArray(m_inputVAO);

	// Input VBO
	glGenBuffers(1, &m_inputBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_inputBuffer);

	// Input Attributes
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
	glEnableVertexAttribArray(VC_ATTRIBUTE_FLAGS);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_BYTE,			GL_FALSE,	sizeof(BlockPoint),	(void*) offsetof(BlockPoint, Position) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		3,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(BlockPoint),	(void*) offsetof(BlockPoint, Color) );
	glVertexAttribIPointer(VC_ATTRIBUTE_FLAGS,		1,	GL_SHORT,						sizeof(BlockPoint),	(void*) offsetof(BlockPoint, Flags) );

	glBindVertexArray(0);


	// =====   Feedback Buffer   ======================================================

	// Feedback VAO
	glGenVertexArrays(1, &m_feedbackVAO);
	glBindVertexArray(m_feedbackVAO);

	// Feedback VBO
	glGenBuffers(1, &m_feedbackBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_feedbackBuffer);

	// Feedback Attributes ( Remember: The Attributes interleaved in the buffer are defined by the TerrainCreationShader Pre-Link )
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	//glEnableVertexAttribArray(VC_ATTRIBUTE_NORMAL);
	//glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	4,	GL_FLOAT,	GL_FALSE,	sizeof(GLfloat) * 4,	(void*) 0 );
	//glVertexAttribPointer(VC_ATTRIBUTE_NORMAL,		3,	GL_FLOAT,	GL_FALSE,	sizeof(GLfloat) * 10,	(void*) (sizeof(GLfloat) * 4) );
	//glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		3,	GL_FLOAT,	GL_TRUE,	sizeof(GLfloat) * 10,	(void*) (sizeof(GLfloat) * 7) );

	// Pre-Allocate memory on the GPU for this ( Might move this to ::Rebuild() later to compact it )
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 1000000, NULL, GL_STATIC_DRAW);

	glBindVertexArray(0);


	// =====   Feedback Object   ======================================================

	// Feedback Object
	glGenTransformFeedbacks(1, &m_transformFeedbackObject);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedbackObject);

	// Link output VBO ( m_feedbackBuffer ) with the TF Object
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_feedbackBuffer); 

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);


	glErrorCheck();
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
	m_inputVCount = 0;
	float startTime = VCTime::CurrentTime;

	m_rebuildVerticies = (BlockPoint*) malloc(sizeof(BlockPoint) * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH);

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

				// Upper
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags | 1;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z - 1).IsSolid() ) flags = flags | 2;
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags | 4;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z + 1).IsSolid() ) flags = flags | 8;

				// Middle
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags | 16;
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags | 32;
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags | 64;
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags | 128;

				// Lower
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y - 1, m_blockZ + z).IsSolid() ) flags = flags | 256;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z - 1).IsSolid() ) flags = flags | 512;
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY - y + 1, m_blockZ + z).IsSolid() ) flags = flags | 1024;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z + 1).IsSolid() ) flags = flags | 2048;

				// Occluding blocks
				if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z).IsSolid() ) flags = flags | 4096;
				if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z).IsSolid() ) flags = flags | 8192;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags | 16384;
				if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags | 32768;

				m_rebuildVerticies[m_inputVCount++] = BlockPoint(GLubyte3(x, y, z), GLubyte3(thisType.Color.x, thisType.Color.y, thisType.Color.z), flags );
				// =========  END of make block  ========
			}
		}
	}

	// Empty?
	m_isEmpty = m_inputVCount == 0;
	if (m_isEmpty)
	{
		m_renderStage1->ExectionType = VCRenderStage::Never;
		m_renderStage2->ExectionType = VCRenderStage::Never;

		// release heap malloc
		free(m_rebuildVerticies);
		m_rebuildVerticies = NULL;

		return;
	}

	// Update Input VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_inputBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BlockPoint) * m_inputVCount, &m_rebuildVerticies[0] , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_renderStage1->ExectionType = VCRenderStage::Once;
	m_renderStage2->ExectionType = VCRenderStage::Always;

	// release heap malloc
	free(m_rebuildVerticies);
	m_rebuildVerticies = NULL;

	//std::std::cout << "Chunk rebuilt finished with " << m_vertexCount << " vertices and took " << (VCTime::CurrentTime - startTime) << " seconds." << std::endl;

	glErrorCheck();
}

void VCChunk::RenderStage1()
{
	// Shouldn't get here though
	if ( m_isEmpty )
		return;
	
	glEnable(GL_RASTERIZER_DISCARD);

	// Bind Input VAO
	glBindVertexArray(m_inputVAO);

	// Bind Feedback Object ( Remember: It's already linked with the output buffer m_feedbackBuffer )
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedbackObject);

	// Draw Feedback
	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, m_quary); 
	glBeginTransformFeedback(GL_TRIANGLES);
		glDrawArrays(GL_POINTS, 0, m_inputVCount);
	glEndTransformFeedback();
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN); 

	//glBeginTransformFeedback(GL_TRIANGLES);
	//	glDrawArrays(GL_POINTS, 0, m_inputVCount);
	//glEndTransformFeedback();

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glBindVertexArray(0);
	glDisable(GL_RASTERIZER_DISCARD);

	glErrorCheck();
}

void VCChunk::RenderStage2()
{
	GLuint PrimitivesWritten = 0;
	glGetQueryObjectuiv(m_quary, GL_QUERY_RESULT, &PrimitivesWritten);


	glBindBuffer(GL_ARRAY_BUFFER, m_feedbackBuffer);
	float* arra = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	float* copy = (float*) malloc(sizeof(GLfloat) * 4 * 3 * PrimitivesWritten);
	memcpy(copy, arra, sizeof(GLfloat) * 4 * 3 * PrimitivesWritten);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_feedbackVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_feedbackBuffer);

	const GLfloat testTriangle[12] = {
		0, 0, -1, 1,
		1, 0, -1, 1,
		0, 1, -1, 1
	};

	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	4,	GL_FLOAT,	GL_FALSE,	sizeof(GLfloat) * 4,	(void*) 0 );
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, testTriangle, GL_STATIC_DRAW);

	// MVP
	/*VCGLRenderer::Instance->SetModelMatrix(glm::translate(
		(float)m_x * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_y * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
		(float)m_z * BLOCK_RENDER_SIZE * CHUNK_WIDTH));*/

	glDrawArrays(GL_TRIANGLES, 0, 1);
	glBindVertexArray(0);
	glErrorCheck();

	free(copy);
	//// Bind the Feedback VAO ( Remember: the Feedback's buffer was filled by the last stage )
	//glBindVertexArray(m_feedbackVAO);
	//glErrorCheck();

	//// MVP
	//VCGLRenderer::Instance->SetModelMatrix(glm::translate(
	//	(float)m_x * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
	//	(float)m_y * BLOCK_RENDER_SIZE * CHUNK_WIDTH, 
	//	(float)m_z * BLOCK_RENDER_SIZE * CHUNK_WIDTH));

	//// Draw ( From the Feedback Buffer, bound to the TF Object )
	//glDrawTransformFeedbackStream(GL_TRIANGLES, m_transformFeedbackObject, 0);

	//glBindVertexArray(0);
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