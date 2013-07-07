#include "TestClass.h"
#include "VCGLRenderer.h"


TestClass::TestClass(void)
{
	m_chunk = NULL;
}


TestClass::~TestClass(void)
{
}

void TestClass::Initialize()
{
	m_chunk = new VCChunk(0, 0, 0, NULL);
	m_chunk->Generate();
	m_chunk->StartRebuild();
	m_chunk->ContinueRebuild(0.0f);
//
//    m_bufferId = 0;
//    glGenBuffers(1, &m_bufferId);
//    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
//    
//	ZERO_CHECK(m_bufferId);
//    
//    float m_verts[9] =
//    {
//        0.0f, 0.0f, -1.0f,
//        0.0f, 1.0f, -1.0f,
//        1.0f, 0.0f, -1.0f
//    };
//    
//    glm::perspective(65.0f, 4.0f / 3.0f, 0.1f, 400.0f);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, &m_verts[0] , GL_STATIC_DRAW);
    
	glErrorCheck();
}

void TestClass::Render()
{
	VCGLRenderer::VoxelShader->Bind();
    m_chunk->Render();
    
//    VCGLRenderer::VoxelShader->Bind();
//    glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
//    glErrorCheck();
//    
//	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
//    glErrorCheck();
//    
//	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_BYTE,			GL_FALSE,	sizeof(float) * 3,	0 );
//    glErrorCheck();
//	
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//    glErrorCheck();
//    
//	// Release
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glErrorCheck();
//    
//	glDisableVertexAttribArray(VC_ATTRIBUTE_POSITION);

    glErrorCheck();
}


