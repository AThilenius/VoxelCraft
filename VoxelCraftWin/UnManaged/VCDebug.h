//
//  VCDebug.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCIRenderable.h"
#include "VCGLRenderer.h"

#define MAX_LINE_COUNT 1000000

struct LineVerticie
{
	LineVerticie(){}
	LineVerticie(glm::vec3 position, GLubyte4 color) : Position(GLfloat3(position.x, position.y, position.z)), Color(color){}

	GLfloat3 Position;
	GLubyte4 Color;
};

class VCDebug : VCIRenderable
{
public:
	VCDebug(void);
	~VCDebug(void);

	void Initialize()
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

	static void Reset()
	{
		

	}

	static void DrawLine (glm::vec3 from, glm::vec3 to, GLubyte4 color)
	{
		if (m_lineVertCount + 2 >= MAX_LINE_COUNT)
		{
			VC_ERROR("Too many VCDebug line verticies.");
		}

		m_lineVerts[m_lineVertCount++] = LineVerticie(from, color);
		m_lineVerts[m_lineVertCount++] = LineVerticie(to, color);
	}

	static void DrawCube (glm::vec3 corner, glm::vec3 scale, GLubyte4 color)
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

	virtual VCRenderState* GetState()
	{
		return VCGLRenderer::Instance->PassThroughState;
	}

	virtual void Render()
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
	}


private:
	static int m_lineVertCount;
	static GLuint m_VAO;
	static GLuint m_VBO;
	static LineVerticie m_lineVerts[MAX_LINE_COUNT];

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

void VCInteropDebugReset();
void VCInteropDebugDrawLine (glm::vec3 from, glm::vec3 to, vcint4 color);
void VCInteropDebugDrawCube (glm::vec3 corner, glm::vec3 scale, vcint4 color);