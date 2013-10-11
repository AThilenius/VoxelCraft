//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGLRenderer.h"

#include "VCLexicalEngine.h"
#include "VCWindow.h"

VCGLRenderer* VCGLRenderer::Instance;
VCRenderState* VCGLRenderer::PassThroughState;

VCGLRenderer::VCGLRenderer(void):
	DepthFrameBuffer(0),
	DefaultFrameBuffer(0)
{
	VCGLRenderer::Instance = this;
    glErrorCheck();
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

	ShadowShader = new VCShadowShader();
	ShadowShader->Initialize();

	LexShader = new VCLexShader();
	LexShader->Initialize();

	TextureShader = new VCTextureShader();
	TextureShader->Initialize();

	VoxelShader = new VCVoxelShader();
	VoxelShader->Initialize();

	GuiShader = new VCGuiShader();
	GuiShader->Initialize();

	ColorPassThroughShader = new VCColorPassThroughShader();
	ColorPassThroughShader->Initialize();

	CreateDepthFrameBuffer();


	// ===================    Quad for visualize    =======================================
	// The quad's FBO. Used only for visualizing the shadowmap.
	glGenVertexArrays(1, &m_quad_VertexArrayID);
	glBindVertexArray(m_quad_VertexArrayID);

	static const GLfloat g_quad_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer( VC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glBindVertexArray(0);

	// Default States:
	VCGLRenderer::PassThroughState = new VCRenderState();
	VCGLRenderer::PassThroughState->Stages[0].FrameBuffer = VCGLRenderer::Instance->DefaultFrameBuffer;
	VCGLRenderer::PassThroughState->Stages[0].Shader = VCGLRenderer::Instance->ColorPassThroughShader;
	VCGLRenderer::PassThroughState->Stages[0].Viewport = RectangleF(0, 0, 0.8f, 0.9f);
	RegisterState(VCGLRenderer::PassThroughState);

    glErrorCheck();
    cout << "VCGLRenderer Initialized" << endl;
}

void VCGLRenderer::Render(int fromBatch, int toBatch)
{
	static int lastFrameBuffer = 0;
	static RectangleF lastViewport;

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
			if (lastViewport.X != state->Stages[stageId].Viewport.X ||
				lastViewport.Y != state->Stages[stageId].Viewport.Y ||
				lastViewport.Width != state->Stages[stageId].Viewport.Width ||
				lastViewport.Height != state->Stages[stageId].Viewport.Height)
			{
				lastViewport = state->Stages[stageId].Viewport;
				int width = VCWindow::Instance->Width;
				int height = VCWindow::Instance->Height;
				glViewport(width * lastViewport.X, height * lastViewport.Y, width * lastViewport.Width, height * lastViewport.Height);
			}

			// Set Shader ( will auto re-assign test )
			state->Stages[stageId].Shader->Bind();

			// Bind Textures
			for ( int texId = 0; texId < MAX_TEXTURES; texId++ )
			{
				if (state->Stages[stageId].Textures[texId] != 0)
				{
					glActiveTexture(GL_TEXTURE0 + texId);
					glBindTexture(GL_TEXTURE_2D, state->Stages[stageId].Textures[texId]);
				}
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

	//// ===================    Visualize    =====================
	//glViewport(0, 0, 256, 256);

	//TextureShader->Bind();

	//// Bind our texture in Texture Unit 0
	//glBindVertexArray(m_quad_VertexArrayID);
	//
	//glActiveTexture(GL_TEXTURE0);
	////glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	//glBindTexture(GL_TEXTURE_2D, DepthTexture);

	//TextureShader->SetTextureUnit(0);

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindVertexArray(0);

}

void VCGLRenderer::SetModelMatrix(mat4 matrix)
{
	Shader::BoundShader->SetModelMatrix(matrix);
}

void VCGLRenderer::RegisterState( VCRenderState* state )
{
	m_renderMap.insert(RenderMap::value_type(state, RenderSet()));
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
		VC_ERROR("Cannot remove RenderState because it is not registered.");
	}

	auto setIter = iter->second.find(renderable);

	if (setIter == iter->second.end())
	{
		VC_ERROR("Cannot remove Renderable because it is not registered.");
	}

	iter->second.erase(setIter);
}

void VCGLRenderer::CreateDepthFrameBuffer()
{
	glGenFramebuffers(1, &DepthFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, DepthFrameBuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &DepthTexture);
	glBindTexture(GL_TEXTURE_2D, DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1280, 600, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	// Also tried using GL_COMPARE_R_TO_TEXTURE with sampler2DShadow in the shader. Same outcome.
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "Failed to initialize GLRenderer!" << endl;
}

void VCGLRenderer::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.GLRenderer::VCInteropRendererRender", (void*)VCInteropRendererRender);
}

void VCInteropRendererRender( int from, int to )
{
	VCGLRenderer::Instance->Render(from, to);
}
