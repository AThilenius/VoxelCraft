//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGLRenderer.h"

VCGLRenderer* VCGLRenderer::Instance;

VCGLRenderer::VCGLRenderer(void):
	m_frameBufferId(0)
{
	VCGLRenderer::Instance == this;

	//VoxelShader = new VCVoxelShader();
    ShadowShader = new VCShadowShader();

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
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	//VoxelShader->Initialize();
	ShadowShader->Initialize();

	// ================    Create Frame-buffer for shadows    =============================
	glGenFramebuffers(1, &m_frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);	

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "Failed to initialize GLRenderer!" << endl;

	VoxelShader = new VCVoxelShader(m_depthTexture);
	VoxelShader->Initialize();

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

	TextureShader = new VCTextureShader();
	TextureShader->Initialize();

    glErrorCheck();
    cout << "VCGLRenderer Initialized" << endl;
}

void VCGLRenderer::Render()
{
	// ====================    Shadow    =====================
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
	glViewport(0, 0, 1024, 1024);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ShadowShader->Bind();
	VCSceneGraph::Instance->RenderGraph();


	// ====================    Diffuse    =====================
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 800);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	VoxelShader->Bind();
	VCSceneGraph::Instance->RenderGraph();


	// ===================    Visualize    =====================
	glViewport(0,0,512,512);

	TextureShader->Bind();

	// Bind our texture in Texture Unit 0
	glBindVertexArray(m_quad_VertexArrayID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	TextureShader->SetTextureUnit(0);

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void VCGLRenderer::SetModelMatrix(mat4 matrix)
{
	Shader::BoundShader->SetModelMatrix(matrix);
}