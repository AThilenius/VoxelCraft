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
#include "VCGui.h"


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
	m_rStage->BatchOrder = VC_BATCH_GUI + 1;
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

void VCImageInstance::DrawImage( VCRectangle frame, float depthStep )
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
	VCTextureVerticie ll (GLfloat3(frame.X,					frame.Y,				 depthStep), GLfloat2(0, 1));
	VCTextureVerticie ul (GLfloat3(frame.X,					frame.Y	+ frame.Height,	 depthStep), GLfloat2(0, 0));
	VCTextureVerticie lr (GLfloat3(frame.X + frame.Width,	frame.Y,				 depthStep), GLfloat2(1, 1));
	VCTextureVerticie ur (GLfloat3(frame.X + frame.Width,	frame.Y	+ frame.Height,	 depthStep), GLfloat2(1, 0));

	m_vertBuffer[m_vertexCount++] = ul;
	m_vertBuffer[m_vertexCount++] = ll;
	m_vertBuffer[m_vertexCount++] = lr;

	m_vertBuffer[m_vertexCount++] = ul;
	m_vertBuffer[m_vertexCount++] = lr;
	m_vertBuffer[m_vertexCount++] = ur;

	// Queue 1+ run
	m_rStage->ExectionType = VCRenderStage::Once;
}

void VCImageInstance::Draw9Slice( VCRectangle frame, int pizelOffset, float padding, float depthStep )
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

	// Outer
	VCTextureVerticie ll (GLfloat3(frame.X,					frame.Y,				 depthStep), GLfloat2(0, 1));
	VCTextureVerticie ul (GLfloat3(frame.X,					frame.Y	+ frame.Height,	 depthStep), GLfloat2(0, 0));
	VCTextureVerticie lr (GLfloat3(frame.X + frame.Width,	frame.Y,				 depthStep), GLfloat2(1, 1));
	VCTextureVerticie ur (GLfloat3(frame.X + frame.Width,	frame.Y	+ frame.Height,	 depthStep), GLfloat2(1, 0));

	// Rounded scale. SIMD rounding! Cool!
	//glm::vec4 roundedScale ( frame.X * padding, frame.Y * padding, frame.Width * padding, frame.Height * padding );
	//roundedScale = glm::round(roundedScale);
	VCRectangle irect (frame.X + pizelOffset, frame.Y + pizelOffset, frame.Width - (pizelOffset * 2), frame.Height - (pizelOffset * 2));

	// Inner:
	VCTextureVerticie ill (GLfloat3(irect.X,					irect.Y,				 depthStep), GLfloat2(padding,		1 - padding));
	VCTextureVerticie iul (GLfloat3(irect.X,					irect.Y	+ irect.Height,	 depthStep), GLfloat2(padding,		padding));
	VCTextureVerticie ilr (GLfloat3(irect.X + irect.Width,		irect.Y,				 depthStep), GLfloat2(1 - padding,	1 - padding));
	VCTextureVerticie iur (GLfloat3(irect.X + irect.Width,		irect.Y	+ irect.Height,	 depthStep), GLfloat2(1 - padding,	padding));

	// Left:
	VCTextureVerticie leftL (GLfloat3(frame.X,					irect.Y,				 depthStep), GLfloat2(0,			1 - padding));
	VCTextureVerticie leftU (GLfloat3(frame.X,					irect.Y	+ irect.Height,	 depthStep), GLfloat2(0,			padding));

	// Right:
	VCTextureVerticie rightL (GLfloat3(frame.X + frame.Width,	irect.Y,				 depthStep), GLfloat2(1,			1 - padding));
	VCTextureVerticie rightU (GLfloat3(frame.X + frame.Width,	irect.Y	+ irect.Height,	 depthStep), GLfloat2(1,			padding));

	// Top
	VCTextureVerticie topL (GLfloat3(irect.X,					frame.Y	+ frame.Height,  depthStep), GLfloat2(padding,		0));
	VCTextureVerticie topR (GLfloat3(irect.X + irect.Width,		frame.Y	+ frame.Height,	 depthStep), GLfloat2(1 - padding,	0));

	// Bottom
	VCTextureVerticie bottomL (GLfloat3(irect.X,					frame.Y,			depthStep), GLfloat2(padding,		1));
	VCTextureVerticie bottomR (GLfloat3(irect.X + irect.Width,		frame.Y,			depthStep), GLfloat2(1 - padding,	1));

	// Upper Left
	m_vertBuffer[m_vertexCount++] = ul;
	m_vertBuffer[m_vertexCount++] = leftU;
	m_vertBuffer[m_vertexCount++] = topL;

	m_vertBuffer[m_vertexCount++] = leftU;
	m_vertBuffer[m_vertexCount++] = iul;
	m_vertBuffer[m_vertexCount++] = topL;

	// Left
	m_vertBuffer[m_vertexCount++] = leftU;
	m_vertBuffer[m_vertexCount++] = leftL;
	m_vertBuffer[m_vertexCount++] = ill;

	m_vertBuffer[m_vertexCount++] = ill;
	m_vertBuffer[m_vertexCount++] = iul;
	m_vertBuffer[m_vertexCount++] = leftU;

	// Lower Left
	m_vertBuffer[m_vertexCount++] = leftL;
	m_vertBuffer[m_vertexCount++] = ll;
	m_vertBuffer[m_vertexCount++] = bottomL;

	m_vertBuffer[m_vertexCount++] = bottomL;
	m_vertBuffer[m_vertexCount++] = ill;
	m_vertBuffer[m_vertexCount++] = leftL;

	// Lower
	m_vertBuffer[m_vertexCount++] = ill;
	m_vertBuffer[m_vertexCount++] = bottomL;
	m_vertBuffer[m_vertexCount++] = bottomR;

	m_vertBuffer[m_vertexCount++] = bottomR;
	m_vertBuffer[m_vertexCount++] = ilr;
	m_vertBuffer[m_vertexCount++] = ill;

	// Lower Right
	m_vertBuffer[m_vertexCount++] = ilr;
	m_vertBuffer[m_vertexCount++] = bottomR;
	m_vertBuffer[m_vertexCount++] = lr;

	m_vertBuffer[m_vertexCount++] = lr;
	m_vertBuffer[m_vertexCount++] = rightL;
	m_vertBuffer[m_vertexCount++] = ilr;

	// Right
	m_vertBuffer[m_vertexCount++] = iur;
	m_vertBuffer[m_vertexCount++] = ilr;
	m_vertBuffer[m_vertexCount++] = rightL;

	m_vertBuffer[m_vertexCount++] = rightL;
	m_vertBuffer[m_vertexCount++] = rightU;
	m_vertBuffer[m_vertexCount++] = iur;

	// Upper Right
	m_vertBuffer[m_vertexCount++] = topR;
	m_vertBuffer[m_vertexCount++] = iur;
	m_vertBuffer[m_vertexCount++] = rightU;

	m_vertBuffer[m_vertexCount++] = rightU;
	m_vertBuffer[m_vertexCount++] = ur;
	m_vertBuffer[m_vertexCount++] = topR;

	// Upper
	m_vertBuffer[m_vertexCount++] = topL;
	m_vertBuffer[m_vertexCount++] = iul;
	m_vertBuffer[m_vertexCount++] = iur;

	m_vertBuffer[m_vertexCount++] = iur;
	m_vertBuffer[m_vertexCount++] = topR;
	m_vertBuffer[m_vertexCount++] = topL;

	// Middle
	m_vertBuffer[m_vertexCount++] = iul;
	m_vertBuffer[m_vertexCount++] = ill;
	m_vertBuffer[m_vertexCount++] = ilr;

	m_vertBuffer[m_vertexCount++] = ilr;
	m_vertBuffer[m_vertexCount++] = iur;
	m_vertBuffer[m_vertexCount++] = iul;

	// Queue 1+ run
	m_rStage->ExectionType = VCRenderStage::Once;
}


void VCImageInstance::Render()
{
	if (m_vertexCount == 0)
		return;

	VCGLRenderer::Instance->SetModelMatrix(glm::ortho<float>(0, VCWindow::Instance->Width * VCGui::InverseScale, 0, VCWindow::Instance->Height * VCGui::InverseScale, -100000, -1));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VCTextureVerticie) * m_vertexCount, m_vertBuffer , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);

	m_vertexCount = 0;

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	VCGLRenderer::Instance->SetModelMatrix(glm::ortho<float>(0, VCWindow::Instance->Width * VCGui::InverseScale, 0, VCWindow::Instance->Height * VCGui::InverseScale, -100000, -1));

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VCTextureVerticie) * m_vertexCount, m_vertBuffer , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);

	m_vertexCount = 0;
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}