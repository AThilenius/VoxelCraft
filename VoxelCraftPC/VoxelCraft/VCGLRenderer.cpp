#include "VCGLRenderer.h"

// Statics
VCVoxelShader* VCGLRenderer::VoxelShader = NULL;
VCCamera* VCGLRenderer::MainCamera = NULL;


VCGLRenderer::VCGLRenderer(void)
{
	MainCamera = new VCCamera();
	VoxelShader = new VCVoxelShader();
}


VCGLRenderer::~VCGLRenderer(void)
{
}

void VCGLRenderer::Initialize()
{
	// GL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	MainCamera->PreRender();
	VoxelShader->Initialize();

	m_testClass.Initialize();
}

void VCGLRenderer::Render()
{
	VCGLRenderer::MainCamera->PreRender();

	glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ...
	m_testClass.Render();
}