//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLRenderer.h"

#include "VCShadowShader.h"
#include "VCTextureShader.h"
#include "VCLexShader.h"
#include "VCGuiShader.h"
#include "VCColorPassThroughShader.h"
#include "VCTerrainConstructionShader.h"
#include "VCTerrianFeedbackShader.h"

#include "VCLexicalEngine.h"
#include "VCWindow.h"
#include "VCSceneGraph.h"
#include "VCMonoRuntime.h"
#include "VCTexture.h"
#include "VCCamera.h"
#include "VCRenderStage.h"

VCGLRenderer* VCGLRenderer::Instance;

// _VCRenderStageCompare::Operator() Struct
bool _VCRenderStageCompare::operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
{
	return (*lhs) < (*rhs);
}

VCGLRenderer::VCGLRenderer(void):
	DepthFrameBuffer(0),
	DefaultFrameBuffer(0),
	ShadowFallback(false)
{
	VCGLRenderer::Instance = this;
}


VCGLRenderer::~VCGLRenderer(void)
{
}

void VCGLRenderer::Initialize()
{
	// GL Setup
	glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	CreateDepthFrameBuffer();

	ShadowShader = new VCShadowShader();
	ShadowShader->Initialize();

	LexShader = new VCLexShader();
	LexShader->Initialize();

	TextureShader = new VCTextureShader();
	TextureShader->Initialize();

	GuiShader = new VCGuiShader();
	GuiShader->Initialize();

	ColorPassThroughShader = new VCColorPassThroughShader();
	ColorPassThroughShader->Initialize();

	TerrainConstructionShader = new VCTerrainConstructionShader();
	TerrainConstructionShader->Initialize();

	TerrainFeedbackShader = new VCTerrianFeedbackShader();
	TerrainFeedbackShader->Initialize();

    glErrorCheck();
    std::cout << "VCGLRenderer Initialized" << std::endl;
}

void VCGLRenderer::Render(int fromBatch, int toBatch)
{
	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Prep SceneGraph
	VCSceneGraph::Instance->PrepareSceneGraph();

	// For each RenderState
	static VCRenderStage* lastBoundStage = NULL;
	for ( auto setIter = m_renderSet.begin(); setIter != m_renderSet.end(); setIter++ )
	{
		VCRenderStage* stage = *setIter;

		if (stage->ExectionType == VCRenderStage::ExecutionTypes::Never || stage->BatchOrder < fromBatch || stage->BatchOrder > toBatch)
			continue;

		VCRenderStage::TransitionAndExecute(lastBoundStage, stage);
		lastBoundStage = stage;
	}
}

void VCGLRenderer::SetModelMatrix(glm::mat4 matrix)
{
	VCShader::BoundShader->SetModelMatrix(matrix);
}

void VCGLRenderer::RegisterStage( VCRenderStage* stage )
{
	stage->BuildKey();

#ifdef DEBUG
	if (m_renderSet.find(stage) != m_renderSet.end())
	{
		VC_ERROR("Cannot add duplicate render stage!");
	}
#endif

	m_renderSet.insert(stage);
}

void VCGLRenderer::UnRegisterStage( VCRenderStage* stage )
{
	auto iter = m_renderSet.find(stage);

	if (iter == m_renderSet.end())
	{
		VC_ERROR("Cannot remove RenderState because it is not registered.");
	}

	m_renderSet.erase(iter);
}

void VCGLRenderer::CreateDepthFrameBuffer()
{
	glGenFramebuffers(1, &DepthFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrameBuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1280, 600, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to initialize GL Depth frame buffer! Using fall-back." << std::endl;
		ShadowFallback = true;
	}

	DepthTexture = VCTexture::ManageExistingBuffer(depthTex);
}

void VCGLRenderer::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("GLRenderer::VCInteropRendererRender", (void*)VCInteropRendererRender);
}

void VCInteropRendererRender( int from, int to )
{
	VCGLRenderer::Instance->Render(from, to);
}
