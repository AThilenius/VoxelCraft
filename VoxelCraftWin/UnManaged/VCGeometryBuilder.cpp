//
//  VCGeometryBuilder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGeometryBuilder.h"

#include "VCGLRenderer.h"
#include "Shader.h"
#include "VCGuiShader.h"


GuiRectVerticie::GuiRectVerticie()
{

}

GuiRectVerticie::GuiRectVerticie( GLushort2 position, GLubyte4 color ) :
	Position(position),
	Color(color)
{

}

GuiRectVerticie::~GuiRectVerticie()
{

}

VCGeometryBuilder::VCGeometryBuilder( void ) : 
	m_VAO(0), 
	m_VBO(0), 
	m_vCount(0)
{
	// Pre-Compute a unit circle
	for (int i = 0; i < VC_GEOMETRY_RESOLUTION; i++)
	{
		double rad1 = (double)i * 0.314159265;

		m_unitCircle[i] = glm::vec2(
			(float)cos(rad1),
			(float)sin(rad1));
	}
}

VCGeometryBuilder::~VCGeometryBuilder( void )
{

}

void VCGeometryBuilder::DrawRectangle( VCRectangle frame, GLubyte4 color )
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

void VCGeometryBuilder::DrawEllipse( VCPoint centroid, int width, int height, GLubyte4 color )
{
	if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
	{
		VC_ERROR("You have 125000+ Gui rectangles... too much man.");
	}

	glm::vec2 firstRad = m_unitCircle[0];

	// Scale
	firstRad.x *= width;
	firstRad.y *= height;

	// Shift
	firstRad.x += centroid.X;
	firstRad.y += centroid.Y;

	// Truncate
	VCPoint p1 (firstRad.x, firstRad.y);

	for (int i = 1; i < VC_GEOMETRY_RESOLUTION; i++)
	{
		glm::vec2 rad2 = m_unitCircle[i];

		// Scale
		rad2.x *= width;
		rad2.y *= height;

		// Shift
		rad2.x += centroid.X;
		rad2.y += centroid.Y;

		// Truncate
		VCPoint p2 (rad2.x, rad2.y);

		// Add verts ( This way is actually faster... I <3 the profiler )
		m_verts[m_vCount].Position.x = (GLushort)centroid.X;	m_verts[m_vCount].Position.y = (GLushort)centroid.Y;	m_verts[m_vCount++].Color = color;
		m_verts[m_vCount].Position.x = (GLushort)p1.X;			m_verts[m_vCount].Position.y = (GLushort)p1.Y;			m_verts[m_vCount++].Color = color;
		m_verts[m_vCount].Position.x = (GLushort)p2.X;			m_verts[m_vCount].Position.y = (GLushort)p2.Y;			m_verts[m_vCount++].Color = color;

		p1 = p2;
	}
}

void VCGeometryBuilder::AddQuad( GuiRectVerticie vert )
{
	if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
	{
		VC_ERROR("You have 125000+ Gui rectangles... too much man.");
	}

	m_verts[m_vCount++] = vert;
}

void VCGeometryBuilder::Reset()
{

}

void VCGeometryBuilder::Initialize()
{
	// Create a render state for text rendering
	RenderState = new VCRenderState(1);
	RenderState->BatchingOrder = VC_BATCH_GUI_BASE;
	RenderState->Stages[0].Shader = VCGLRenderer::Instance->GuiShader;
	RenderState->Stages[0].DepthTest = false;
	VCGLRenderer::Instance->RegisterState(RenderState);
	VCGLRenderer::Instance->RegisterIRenderable(this);

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
	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

	glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	2,	GL_UNSIGNED_SHORT,	GL_FALSE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Position) );
	glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Color) );

	glBindVertexArray(0);
}

VCRenderState* VCGeometryBuilder::GetState()
{
	return RenderState;
}

void VCGeometryBuilder::Render()
{
	if (m_vCount == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GuiRectVerticie) * m_vCount, m_verts , GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vCount);
	glBindVertexArray(0);

	m_vCount = 0;
}
