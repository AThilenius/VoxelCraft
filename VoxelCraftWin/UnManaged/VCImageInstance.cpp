//
//  VCImageInstance.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCImageInstance.h"
#include "VCRenderStage.h"
#include "VCGLRenderer.h"
#include "VCShader.h"
#include "VCTexturePassThroughShader.h"
#include "VCLexShader.h"
#include "VCWindow.h"


VCTextureVerticie::VCTextureVerticie()
{
}

VCTextureVerticie::VCTextureVerticie( GLfloat3 position, GLfloat2 uv ):
	Position(position),
	UV(uv)
{
}

VCImageInstance::VCImageInstance(std::string path):
	m_path(path),
	m_rStage(NULL),
	m_texturePtr(VCTexturePtr(NULL)),
	m_vertBuffer(NULL),
	m_vertBufferSize(0),
	m_vertexCount(0),
	m_VAO(0),
	m_VBO(0)
{
	m_vertBuffer = new VCTextureVerticie[VC_TEXTURE_BUILDER_START_VERT_SIZE];
	m_vertBufferSize = VC_TEXTURE_BUILDER_START_VERT_SIZE;
}


VCImageInstance::~VCImageInstance(void)
{
	VCGLRenderer::Instance->UnRegisterStage(m_rStage);
	delete[] m_vertBuffer;
	delete m_rStage;
}

void VCImageInstance::Initialize()
{
	// TriLinear filtered texture
	m_texturePtr = VCTexture::Get(m_path);
	
	// Render Stage
	m_rStage = new VCRenderStage(VC_VOID_DELEGATE_METHOD(VCImageInstance, Render));
	m_rStage->ExectionType = VCRenderStage::Never;
	m_rStage->BatchOrder = VC_BATCH_GUI;
	m_rStage->DepthTest = false;
	//m_rStage->Blend = true;
	m_rStage->Shader = VCGLRenderer::Instance->TexturePassthroughShader;
	m_rStage->Texture = m_texturePtr;
	VCGLRenderer::Instance->RegisterStage(m_rStage);

	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	ZERO_CHECK(m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glEnableVertexAttribArray(VC_ATTRIBUTE_TEX_COORD_0);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,		3,	GL_FLOAT,	GL_FALSE,	sizeof(VCTextureVerticie),	(void*) offsetof(VCTextureVerticie, Position) );
	glVertexAttribPointer(VC_ATTRIBUTE_TEX_COORD_0,		2,	GL_FLOAT,	GL_FALSE,	sizeof(VCTextureVerticie),	(void*) offsetof(VCTextureVerticie, UV) );

	glBindVertexArray(0);
}

void VCImageInstance::DrawImage( VCRectangle frame )
{
	// X10 size if needed, never shrink
	if ( m_vertexCount + 6 >= m_vertBufferSize )
	{
		VCTextureVerticie* oldBuffer = m_vertBuffer;
		m_vertBuffer = new VCTextureVerticie[m_vertBufferSize * 10];
		memcpy(m_vertBuffer, oldBuffer, sizeof(VCTextureVerticie) * m_vertBufferSize);
		delete[] oldBuffer;
		m_vertBufferSize *= 10;
	}

	// Remember: DX UV Coordinates (Y inverted)
	VCTextureVerticie ll (GLfloat3(frame.X,					frame.Y,				 0), GLfloat2(0, 1));
	VCTextureVerticie ul (GLfloat3(frame.X,					frame.Y	+ frame.Height,	 0), GLfloat2(0, 0));
	VCTextureVerticie lr (GLfloat3(frame.X + frame.Width,	frame.Y,				 0), GLfloat2(1, 1));
	VCTextureVerticie ur (GLfloat3(frame.X + frame.Width,	frame.Y	+ frame.Height,	 0), GLfloat2(1, 0));

	m_vertBuffer[m_vertexCount++] = ul;
	m_vertBuffer[m_vertexCount++] = ll;
	m_vertBuffer[m_vertexCount++] = lr;

	m_vertBuffer[m_vertexCount++] = ul;
	m_vertBuffer[m_vertexCount++] = lr;
	m_vertBuffer[m_vertexCount++] = ur;

	// Queue 1+ run
	m_rStage->ExectionType = VCRenderStage::Once;
}

void VCImageInstance::Render()
{
	if (m_vertexCount == 0)
		return;

	VCGLRenderer::Instance->SetModelMatrix(glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VCTextureVerticie) * m_vertexCount, m_vertBuffer , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);

	m_vertexCount = 0;
}