//
//  VC3DLineDrawer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/29/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VC3DLineDrawer.h"
#include "VCGLRenderer.h"
#include "VCObjectStore.h"
#include "VCRenderStage.h"
#include "VCCamera.h"
#include "VCGui.h"
#include "VCWindow.h"
#include "VCResourceManager.h"

LineVerticie::LineVerticie():
	Position(glm::vec3()),
	Color(GLubyte4())
{
}

LineVerticie::LineVerticie( glm::vec3 position, GLubyte4 color ):
	Position(position),
	Color(color)
{
}

VC3DLineDrawer::VC3DLineDrawer(VCCamera* camera):
	m_renderStage(NULL),
	m_camera(camera),
	m_lineVertCount(0),
	m_VAO(0),
	m_VBO(0),
	m_warningIssued(false)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VC3DLineDrawer::~VC3DLineDrawer(void)
{
	VCGLRenderer::Instance->UnRegisterStage(m_renderStage);

	// TODO: Release VAO / VBO
}

void VC3DLineDrawer::Initialize()
{
	// =====   Render Stages   ======================================================
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VC3DLineDrawer, &VC3DLineDrawer::Render>(this));
	m_renderStage->Camera = m_camera;
	m_renderStage->Shader = VCResourceManager::GetShader("ColorPassThrough");
	m_renderStage->ExectionType = VCRenderStage::Always;
	VCGLRenderer::Instance->RegisterStage(m_renderStage);

	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	ZERO_CHECK(m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VCShaderAttribute::Position0);
	glEnableVertexAttribArray(VCShaderAttribute::Color0);

	glVertexAttribPointer(VCShaderAttribute::Position0,	3,	GL_FLOAT,			GL_FALSE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Position) );
	glVertexAttribPointer(VCShaderAttribute::Color0,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Color) );

	glBindVertexArray(0);
}

void VC3DLineDrawer::DrawLine( glm::vec3 from, glm::vec3 to, GLubyte4 color )
{
	if (m_warningIssued)
		return;

	else if (m_lineVertCount + 2 >= MAX_LINE_COUNT)
	{
		VC_WARN("Too many VCDebug line verticies.");
		m_warningIssued = true;
		return;
	}

	m_lineVerts[m_lineVertCount++] = LineVerticie(from, color);
	m_lineVerts[m_lineVertCount++] = LineVerticie(to, color);
}

void VC3DLineDrawer::Render()
{
	if (m_lineVertCount == 0)
		return;

	VCShader::BoundShader->SetMVP(VCCamera::BoundCamera->ProjectionViewMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineVerticie) * m_lineVertCount, m_lineVerts , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_LINES, 0, m_lineVertCount);
	glBindVertexArray(0);

	m_lineVertCount = 0;
	m_warningIssued = false;
}

// CTor / DTor
int VCInteropNew3DLineDrawer(int cameraHandle)
{
	VCCamera* camera = (VCCamera*) VCObjectStore::Instance->GetObject(cameraHandle);
	VC3DLineDrawer* newDrawer = new VC3DLineDrawer(camera);
	newDrawer->Initialize();
	return newDrawer->Handle;
}

void VCInteropRelease3DLineDrawer(int handle)
{
	VC3DLineDrawer* obj = (VC3DLineDrawer*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInterop3DLineDrawerDrawLine (int handle, glm::vec3 from, glm::vec3 to, vcint4 color)
{
	VC3DLineDrawer* obj = (VC3DLineDrawer*) VCObjectStore::Instance->GetObject(handle);
	return obj->DrawLine(from, to, GLubyte4(color.X, color.Y, color.Z, color.W) );
}