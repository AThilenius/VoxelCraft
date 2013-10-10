//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCRenderState.h"
#include "VCGLRenderer.h"
#include "VCIRenderable.h"

// 1.00 MB
#define VC_GEOMETRY_MAX_VERT_SIZE 125000

struct GuiRectVerticie
{
	GuiRectVerticie(){}
	~GuiRectVerticie(){}
	GuiRectVerticie(GLushort2 position, GLubyte4 color):
		Position(position),
		Color(color)
	{
	}

	GLushort2 Position;
	GLubyte4 Color;
};

class VCGeometryBuilder : public VCIRenderable
{
public:
	VCGeometryBuilder(void) : m_VAO(0), m_VBO(0), m_vCount(0){}
	~VCGeometryBuilder(void){}

	void DrawRectangle ( Rectangle frame, GLubyte4 color )
	{
		if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
		{
			VC_ERROR("You have 125000+ Gui rectangles... too much man.");
		}

		GuiRectVerticie ll (GLushort2(frame.X,					frame.Y					), color);
		GuiRectVerticie ul (GLushort2(frame.X,					frame.Y	+ frame.Height	), color);
		GuiRectVerticie lr (GLushort2(frame.X + frame.Width,	frame.Y					), color);
		GuiRectVerticie ur (GLushort2(frame.X + frame.Width,	frame.Y	+ frame.Height	), color);

		m_verts[m_vCount++] = ul;
		m_verts[m_vCount++] = ll;
		m_verts[m_vCount++] = lr;

		m_verts[m_vCount++] = ul;
		m_verts[m_vCount++] = lr;
		m_verts[m_vCount++] = ur;
	}

	void Reset()
	{
		m_vCount = 0;

		if (m_VAO != 0)
		{
			glDeleteBuffers(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
			m_VAO = 0;
		}
	}

	void Initialize()
	{
		// Create a render state for text rendering
		RenderState = new VCRenderState();
		RenderState->StageCount = 1;
		RenderState->BatchingOrder = VC_BATCH_GUI_BASE;
		RenderState->Stages[0].Shader = VCGLRenderer::Instance->GuiShader;
		RenderState->Stages[0].DepthTest = false;
		VCGLRenderer::Instance->RegisterState(RenderState);
		VCGLRenderer::Instance->RegisterIRenderable(this);
	}

	virtual VCRenderState* GetState() { return RenderState; }

	virtual void Render()
	{
		if (m_vCount == 0)
			return;

		if (m_VAO == 0)
		{
			// Create VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
			glErrorCheck();

			// Create VBO
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			ZERO_CHECK(m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(GuiRectVerticie) * m_vCount, m_verts , GL_STREAM_DRAW);

			// Bind Attributes
			glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
			glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

			glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	2,	GL_UNSIGNED_SHORT,	GL_FALSE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Position) );
			glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Color) );

			glDrawArrays(GL_TRIANGLES, 0, m_vCount);

			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, m_vCount);
			glBindVertexArray(0);
		}

	}
private:
	VCRenderState* RenderState;

	GLuint m_VAO;
	GLuint m_VBO;
	int m_vCount;
	GuiRectVerticie m_verts[VC_GEOMETRY_MAX_VERT_SIZE];
};

