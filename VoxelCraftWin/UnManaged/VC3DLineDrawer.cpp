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
#include "VCGLBuffer.h"

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
	m_warningIssued(false),
	m_gpuBuffer(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VC3DLineDrawer::~VC3DLineDrawer(void)
{
	VCGLRenderer::Instance->UnRegisterStage(m_renderStage);
	SAFE_DELETE(m_gpuBuffer);
}

void VC3DLineDrawer::Initialize()
{
	// =====   Render Stages   ======================================================
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VC3DLineDrawer, &VC3DLineDrawer::Render>(this));
	m_renderStage->Camera = m_camera;
	m_renderStage->Shader = VCResourceManager::GetShader("ColorPassThrough");
	m_renderStage->ExectionType = VCRenderStage::Always;
	VCGLRenderer::Instance->RegisterStage(m_renderStage);

	m_gpuBuffer = new VCGLBuffer();
	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexAttribute(VCShaderAttribute::Position0,	3, VCGLPrimitives::Float,			false,	sizeof(LineVerticie),	offsetof(LineVerticie, Position))
		.SetVertexAttribute(VCShaderAttribute::Color0,		4, VCGLPrimitives::UnsignedByte,	true,	sizeof(LineVerticie),	offsetof(LineVerticie, Color));
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

	VCGLShader::BoundShader->SetModelMatrix(VCCamera::BoundCamera->ProjectionViewMatrix);

	m_gpuBuffer->VertexBufferSpecification(VCGLDrawPrimitives::LInes)
		.SetVertexData(sizeof(LineVerticie) * m_lineVertCount, m_lineVerts, m_lineVertCount);

	m_gpuBuffer->Draw();

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