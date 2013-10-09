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
	LineVerticie(vec3 position, GLubyte4 color) : Position(GLfloat3(position.x, position.y, position.z)), Color(color){}

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
	}

	static void Reset()
	{
		VCDebug::m_lineVertCount = 0;

		if (VCDebug::m_VAO != 0)
		{
			glDeleteBuffers(1, &VCDebug::m_VAO);
			glDeleteBuffers(1, &VCDebug::m_VBO);
			VCDebug::m_VAO = 0;
		}
	}

	static void DrawLine (vec3 from, vec3 to, GLubyte4 color)
	{
		if (m_lineVertCount + 2 >= MAX_LINE_COUNT)
		{
			VC_ERROR("Too many VCDebug line verticies.");
		}

		m_lineVerts[m_lineVertCount++] = LineVerticie(from, color);
		m_lineVerts[m_lineVertCount++] = LineVerticie(to, color);
	}

	static void DrawCube (vec3 corner, vec3 scale, GLubyte4 color)
	{
		vec3 V1 = corner + vec3(0,			0,			0);
		vec3 V2 = corner + vec3(scale.x,	0,			0);
		vec3 V3 = corner + vec3(scale.x,	0,			scale.z);
		vec3 V4 = corner + vec3(0,			0,			scale.z);

		vec3 V5 = corner + vec3(0,			scale.y,	0);
		vec3 V6 = corner + vec3(scale.x,	scale.y,	0);
		vec3 V7 = corner + vec3(scale.x,	scale.y,	scale.z);
		vec3 V8 = corner + vec3(0,			scale.y,	scale.z);

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

		VCGLRenderer::Instance->SetModelMatrix(mat4());

		if (VCDebug::m_VAO == 0)
		{
			// Create VAO
			glGenVertexArrays(1, &VCDebug::m_VAO);
			glBindVertexArray(VCDebug::m_VAO);
			glErrorCheck();

			// Create VBO
			glGenBuffers(1, &VCDebug::m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VCDebug::m_VBO);
			ZERO_CHECK(VCDebug::m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(LineVerticie) * VCDebug::m_lineVertCount, VCDebug::m_lineVerts , GL_STREAM_DRAW);

			// Bind Attributes
			glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
			glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

			glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	3,	GL_FLOAT,			GL_FALSE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Position) );
			glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(LineVerticie),	(void*) offsetof(LineVerticie, Color) );

			//glDrawArrays(GL_LINES, 0, VCDebug::m_lineVertCount);

			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(VCDebug::m_VAO);
			//glDrawArrays(GL_LINES, 0, VCDebug::m_lineVertCount);
			glBindVertexArray(0);
		}
	}


private:
	static int m_lineVertCount;
	static GLuint m_VAO;
	static GLuint m_VBO;
	static LineVerticie m_lineVerts[MAX_LINE_COUNT];

};

