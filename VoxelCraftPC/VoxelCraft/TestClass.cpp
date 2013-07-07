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

	glErrorCheck("Test Class - Initialize");
}

void TestClass::Render()
{

	VCGLRenderer::VoxelShader->Bind();

	m_chunk->Render();
}


