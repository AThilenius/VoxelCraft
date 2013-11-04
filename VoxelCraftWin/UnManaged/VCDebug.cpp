//
//  VCDebug.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCDebug.h"
#include "VCMonoRuntime.h"

bool VCDebug::m_warningIssued = false;
int VCDebug::m_lineVertCount = 0;
LineVerticie VCDebug::m_lineVerts[] = {};
GLuint VCDebug::m_VAO = 0;
GLuint VCDebug::m_VBO = 0;

LineVerticie::LineVerticie()
{

}

LineVerticie::LineVerticie( glm::vec3 position, GLubyte4 color ) : Position(GLfloat3(position.x, position.y, position.z)), Color(color)
{

}


VCDebug::VCDebug(void)
{
}


VCDebug::~VCDebug(void)
{
}

void VCDebug::Initialize()
{
	VCGLRenderer::Instance->RegisterIRenderable(this);

	// Create VAO
	glGenVertexArrays(1, &VCDebug::m_VAO);
	glBindVertexArray(VCDebug::m_VAO);
	glErrorCheck();

	// Create VBO
	glGenBuffers(1, &VCDebug::m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VCDebug::m_VBO);
	ZERO_CHECK(VCDebug::m_VBO);

	// Bind Attributes
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_FLOAT,			GL_FALSE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Position) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Color) );

	glBindVertexArray(0);
}

void VCDebug::DrawLine( glm::vec3 from, glm::vec3 to, GLubyte4 color )
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

void VCDebug::DrawCube( glm::vec3 corner, glm::vec3 scale, GLubyte4 color )
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

VCRenderState* VCDebug::GetState()
{
	return VCGLRenderer::Instance->PassThroughState;
}

void VCDebug::Render()
{
	if (VCDebug::m_lineVertCount == 0)
		return;

	VCGLRenderer::Instance->SetModelMatrix(glm::mat4());

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineVerticie) * m_lineVertCount, m_lineVerts , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_LINES, 0, m_lineVertCount);
	glBindVertexArray(0);

	m_lineVertCount = 0;
	m_warningIssued = false;
}

void VCDebug::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("Debug::VCInteropDebugReset",		(void*) VCInteropDebugReset);
	VCMonoRuntime::SetMethod("Debug::VCInteropDebugDrawLine",	(void*) VCInteropDebugDrawLine);
	VCMonoRuntime::SetMethod("Debug::VCInteropDebugDrawCube",	(void*) VCInteropDebugDrawCube);
}

void VCInteropDebugReset()
{
	// Stub
}

void VCInteropDebugDrawLine (glm::vec3 from, glm::vec3 to, vcint4 color)
{
	VCDebug::DrawLine(from, to, GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropDebugDrawCube (glm::vec3 corner, glm::vec3 scale, vcint4 color)
{
	VCDebug::DrawCube(corner, scale, GLubyte4(color.X, color.Y, color.Z, color.W));
}