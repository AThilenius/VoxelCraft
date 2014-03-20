//
//  VCLineDrawer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/11/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCLineDrawer.h"
#include "VCRenderStage.h"
#include "VCGLShader.h"
#include "VCGLBuffer.h"


VCLineDrawer::VCLineDrawer(void):
	m_warningIssued(false),
	m_lineVertCount(0),
	m_renderStage(NULL),
	m_gpuBuffer(NULL)
{
}


VCLineDrawer::~VCLineDrawer(void)
{
	SAFE_DELETE(m_gpuBuffer);
}

void VCLineDrawer::Initialize()
{
	// Create Render Stage
	//m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VCLineDrawer, &VCLineDrawer::Render>(this));
	//m_renderStage->BatchOrder = VC_BATCH_GUI;
	//m_renderStage->Shader = VCGLRenderer::Instance->ColorPassThroughShader;
	//m_renderStage->DepthTest = false;
	//VCGLRenderer::Instance->RegisterStage(m_renderStage);

	m_gpuBuffer = new VCGLBuffer();
	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexAttribute(VCShaderAttribute::Position0,	3, VCGLPrimitives::Float,			false,	sizeof(LineVerticie),	offsetof(LineVerticie, Position))
		.SetVertexAttribute(VCShaderAttribute::Color0,		4, VCGLPrimitives::UnsignedByte,	true,	sizeof(LineVerticie),	offsetof(LineVerticie, Color));
}

void VCLineDrawer::DrawLine( glm::vec3 from, glm::vec3 to, GLubyte4 color )
{
	if (m_warningIssued)
		return;

	else if (m_lineVertCount + 2 >= MAX_LINE_COUNT)
	{
		VC_WARN("Too many VCDebug line verticies.");
		m_warningIssued = true;
	}

	m_lineVerts[m_lineVertCount++] = LineVerticie(from, color);
	m_lineVerts[m_lineVertCount++] = LineVerticie(to, color);
}

void VCLineDrawer::DrawCube( glm::vec3 corner, glm::vec3 scale, GLubyte4 color )
{
	glm::vec3 V1 = corner + glm::vec3(0,			0,			0);
	glm::vec3 V2 = corner + glm::vec3(scale.x,	0,			0);
	glm::vec3 V3 = corner + glm::vec3(scale.x,	0,			scale.z);
	glm::vec3 V4 = corner + glm::vec3(0,			0,			scale.z);

	glm::vec3 V5 = corner + glm::vec3(0,			scale.y,	0);
	glm::vec3 V6 = corner + glm::vec3(scale.x,	scale.y,	0);
	glm::vec3 V7 = corner + glm::vec3(scale.x,	scale.y,	scale.z);
	glm::vec3 V8 = corner + glm::vec3(0,			scale.y,	scale.z);

	// Bot
	DrawLine(V1, V2, color);
	DrawLine(V2, V3, color);
	DrawLine(V3, V4, color);
	DrawLine(V4, V1, color);

	// Top
	DrawLine(V5, V6, color);
	DrawLine(V6, V7, color);
	DrawLine(V7, V8, color);
	DrawLine(V8, V5, color);

	// Vertical
	DrawLine(V1, V5, color);
	DrawLine(V2, V6, color);
	DrawLine(V3, V7, color);
	DrawLine(V4, V8, color);
}

void VCLineDrawer::Render()
{
	if (m_lineVertCount == 0)
		return;

	//VCGLRenderer::Instance->SetModelMatrix(glm::mat4());

	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexData(sizeof(LineVerticie) * m_lineVertCount, m_lineVerts, m_lineVertCount, VCGLDrawModes::Stream);

	m_gpuBuffer->Draw();

	m_lineVertCount = 0;
	m_warningIssued = false;
}