//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLRenderer.h"

#include "VCIRenderable.h"
#include "VCShadowShader.h"
#include "VCTextureShader.h"
#include "VCLexShader.h"
#include "VCGuiShader.h"
#include "VCColorPassThroughShader.h"
#include "VCTerrianShader.h"

#include "VCLexicalEngine.h"
#include "VCWindow.h"
#include "VCSceneGraph.h"
#include "VCMonoRuntime.h"
#include "VCTexture.h"
#include "VCRenderState.h"
#include "VCCamera.h"

VCGLRenderer* VCGLRenderer::Instance;
VCRenderState* VCGLRenderer::PassThroughState;

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

	TerrainShader = new VCTerrianShader();
	TerrainShader->Initialize();

	// Default States:
	VCGLRenderer::PassThroughState = new VCRenderState(1);
	VCGLRenderer::PassThroughState->Stages[0].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
	VCGLRenderer::PassThroughState->Stages[0].Shader = VCGLRenderer::Instance->ColorPassThroughShader;
	RegisterState(VCGLRenderer::PassThroughState);

    glErrorCheck();
    std::cout << "VCGLRenderer Initialized" << std::endl;
}

void VCGLRenderer::Render(int fromBatch, int toBatch)
{
	static int lastFrameBuffer = 0;
	static VCRectangle lastViewport;

	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Prep SceneGraph
	VCSceneGraph::Instance->PrepareSceneGraph();

	// For each RenderState
	for ( auto mapIter = m_renderMap.begin(); mapIter != m_renderMap.end(); mapIter++ )
	{
		VCRenderState* state = mapIter->first;

		if (state->BatchingOrder < fromBatch || state->BatchingOrder > toBatch)
			continue;

		// For each stage in the rState
		for ( int stageId = 0; stageId < state->StageCount; stageId++ )
		{

			// Set Framebuffer
			GLuint frameBuffer = state->Stages[stageId].FrameBuffer;
			if (lastFrameBuffer != frameBuffer)
			{
				lastFrameBuffer = frameBuffer;
				glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			}

			// Set Viewport
			if (state->Camera == NULL && lastViewport != VCWindow::Instance->FullViewport)
			{
				// Default full screen
				lastViewport = VCWindow::Instance->FullViewport;
				glViewport(lastViewport.X, lastViewport.Y, lastViewport.Width, lastViewport.Height);
			}

			else if (state->Camera->Viewport != lastViewport)
			{
				// Use Camera's Viewport
				lastViewport = state->Camera->Viewport;
				glViewport(lastViewport.X, lastViewport.Y, lastViewport.Width, lastViewport.Height);
			}

			// Set Shader ( will auto re-assign test )
			state->Stages[stageId].Shader->Bind(state->Camera);

			// Bind Textures
			for ( int texId = 0; texId < state->Stages[stageId].Textures.size(); texId++ )
			{
				if (state->Stages[stageId].Textures[texId] != 0)
					state->Stages[stageId].Textures[texId]->Bind(texId);
			}

			// Bind DepthTest
			if (state->Stages[stageId].DepthTest)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);

			// Bind Blend
			if (state->Stages[stageId].Blend)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);

			// Render everything using this state
			for ( auto iRendIter = mapIter->second.begin(); iRendIter != mapIter->second.end(); iRendIter++ )
				(*iRendIter)->Render();

		}

	}

}

void VCGLRenderer::SetModelMatrix(glm::mat4 matrix)
{
	VCShader::BoundShader->SetModelMatrix(matrix);
}

void VCGLRenderer::RegisterState( VCRenderState* state )
{
#ifdef DEBUG
	if (m_renderMap.find(state) != m_renderMap.end())
	{
		VC_ERROR("Cannot add duplicate render state!");
	}

	std::cout << "VCGLRenderer::RegisterState - " << m_renderMap.size() + 1 << std::endl;
#endif

	m_renderMap.insert(RenderMap::value_type(state, RenderSet()));
}

void VCGLRenderer::UnRegisterState( VCRenderState* state )
{
	auto iter = m_renderMap.find(state);

	if (iter == m_renderMap.end())
	{
		VC_ERROR("Cannot remove RenderState because it is not registered.");
	}

	m_renderMap.erase(iter);
}

void VCGLRenderer::RegisterIRenderable( VCIRenderable* renderable )
{
	auto iter = m_renderMap.find(renderable->GetState());

	if (iter == m_renderMap.end())
	{
		VC_ERROR("UnRegistered state");
	}

	iter->second.insert(RenderSet::value_type(renderable));
}

void VCGLRenderer::UnRegisterIRenderable( VCIRenderable* renderable )
{
	auto iter = m_renderMap.find(renderable->GetState());

	if (iter == m_renderMap.end())
	{
		VC_ERROR("Cannot remove IRenderable from RenderState because the state it is not registered.");
	}

	auto setIter = iter->second.find(renderable);

	if (setIter == iter->second.end())
	{
		VC_ERROR("Cannot remove IRenderable because it is not registered with the state.");
	}

	iter->second.erase(setIter);
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
		std::cout << "Failed to initialize GL Depth frame buffer! Using fallback." << std::endl;
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
