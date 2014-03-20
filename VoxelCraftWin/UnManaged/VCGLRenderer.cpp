//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLRenderer.h"
#include "VCGLShader.h"
#include "VCLexicalEngine.h"
#include "VCGLWindow.h"
#include "VCGLTexture.h"
#include "VCCamera.h"
#include "VCRenderStage.h"
#include "VCResourceManager.h"
#include "VCIRenderable.h"

VCGLRenderer* VCGLRenderer::Instance = NULL;

// _VCRenderStageCompare::Operator() Struct
bool _VCRenderStageCompare::operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
{
	return (*lhs) < (*rhs);
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
#ifdef SHOW_GL_WARNINGS
	char debSource[16], debType[20], debSev[5];
	if(source == GL_DEBUG_SOURCE_API_ARB)
		strcpy(debSource, "OpenGL");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
		strcpy(debSource, "Windows");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
		strcpy(debSource, "Shader Compiler");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
		strcpy(debSource, "Third Party");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
		strcpy(debSource, "Application");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
		strcpy(debSource, "Other");

	if(type == GL_DEBUG_TYPE_ERROR_ARB)
		strcpy(debType, "Error");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
		strcpy(debType, "Deprecated behavior");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
		strcpy(debType, "Undefined behavior");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
		strcpy(debType, "Portability");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
		strcpy(debType, "Performance");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)
		strcpy(debType, "Other");

	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
	{
		strcpy(debSev, "High");
		//SetConsoleColor(Red);
		//printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
		//	debSource,debType,id,debSev,message);
		//std::cin.ignore();
		VCLog::Error("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");
	}

	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
	{
		strcpy(debSev, "Medium");
		//SetConsoleColor(Red);
		//printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
		//	debSource,debType,id,debSev,message);
		//std::cin.ignore();
		VCLog::Error("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");
	}

	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
	{
		static std::set<std::string> postedWarnings;

		strcpy(debSev, "Low");
		std::string post = std::string("Source:") + debSource + "\nType:" + debType + "\nID:" + std::to_string(id) + "\nSeverity:" + debSev + "\nMessage:" + message + "\n";

		if(postedWarnings.find(post) == postedWarnings.end())
		{
			//SetConsoleColor(Yellow);
			//printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
			//	debSource,debType,id,debSev,message);

			//SetConsoleColor(White);
			VCLog::Warning("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");

			postedWarnings.insert(post);
		}
	}

#endif
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
	// =====   Debug   ======================================================
	#if DEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallbackARB(&glDebugCallback, NULL);
	#endif


	// GL Setup
	glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	CreateDepthFrameBuffer();

    glErrorCheck();
	VCLog::Info("VCGLRenderer Initialized", "Initialize");
}

void VCGLRenderer::Render(int fromBatch, int toBatch)
{
	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// For each RenderState
	static VCRenderStage* lastBoundStage = NULL;
	for ( auto setIter = m_renderSet.begin(); setIter != m_renderSet.end(); setIter++ )
	{
		VCRenderStage* stage = *setIter;

		// Clear Depth Buffer for GUI
		if (stage->BatchOrder == VC_BATCH_GUI_BASE && lastBoundStage != NULL && lastBoundStage->BatchOrder != stage->BatchOrder)
			glClear(GL_DEPTH_BUFFER_BIT);

		if (stage->ExectionType == VCRenderStage::ExecutionTypes::Never || stage->BatchOrder < fromBatch || stage->BatchOrder > toBatch)
			continue;

		VCRenderStage::TransitionAndExecute(lastBoundStage, stage);
		lastBoundStage = stage;
	}

	// For each IRenderable
	for ( auto iter = m_renderables.begin(); iter != m_renderables.end(); iter++ )
	{
		VCIRenderable* renderable = *iter;
		renderable->Render();
	}

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
		VCLog::Info("Failed to initialize GL Depth frame buffer! Using fall-back.", "Initialize");
		ShadowFallback = true;
	}

	DepthTexture = VCResourceManager::GetTexure(depthTex);
}

void VCGLRenderer::AddRenderable( VCIRenderable* renderable )
{
	m_renderables.insert(renderable);
}

void VCInteropRendererRender( int from, int to )
{
	VCGLRenderer::Instance->Render(from, to);
}
