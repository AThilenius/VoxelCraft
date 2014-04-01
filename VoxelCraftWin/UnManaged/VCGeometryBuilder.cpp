//
//  VCGeometryBuilder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGeometryBuilder.h"

#include "VCGLShader.h"
#include "VCRenderStage.h"
#include "VCGLWindow.h"
#include "VCGui.h"
#include "VCResourceManager.h"
#include "VCGLBuffer.h"


GuiRectVerticie::GuiRectVerticie()
{

}

GuiRectVerticie::GuiRectVerticie( GLshort3 position, GLubyte4 color ) :
	Position(position),
	Color(color)
{

}

GuiRectVerticie::~GuiRectVerticie()
{

}

VCGeometryBuilder::VCGeometryBuilder(VCGui* gui): 
	m_vCount(0),
	m_gpuBuffer(NULL),
	m_parentGui(gui)
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
	SAFE_DELETE(m_gpuBuffer);
}

void VCGeometryBuilder::DrawRectangle( VCRectangle frame, GLubyte4 color, float depthStep )
{
	if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
		VCLog::Error("You have 125000+ Gui rectangles... too much man.", "Rendering");

	GuiRectVerticie ll (GLshort3(frame.X,					frame.Y,				depthStep), color);
	GuiRectVerticie ul (GLshort3(frame.X,					frame.Y	+ frame.Height,	depthStep), color);
	GuiRectVerticie lr (GLshort3(frame.X + frame.Width,		frame.Y,				depthStep), color);
	GuiRectVerticie ur (GLshort3(frame.X + frame.Width,		frame.Y	+ frame.Height,	depthStep), color);

	m_verts[m_vCount++] = ul;
	m_verts[m_vCount++] = ll;
	m_verts[m_vCount++] = lr;

	m_verts[m_vCount++] = ul;
	m_verts[m_vCount++] = lr;
	m_verts[m_vCount++] = ur;
}

void VCGeometryBuilder::DrawEllipse( VCPoint centroid, int width, int height, GLubyte4 top, GLubyte4 bottom, float depthStep )
{
	if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
		VCLog::Error("You have 125000+ Gui rectangles... too much man.", "Rendering");

	glm::vec2 firstRad = m_unitCircle[0];

	// Color
	GLubyte4 c1;
	GLubyte4::Lerp(c1, bottom, top, (firstRad.y + 1) * 0.5f);

	// Centroid Color
	GLubyte4 centroidC;
	GLubyte4::Lerp(centroidC, bottom, top, 0.5f);

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

		// Colors
		GLubyte4 c2;
		GLubyte4::Lerp(c2, bottom, top, (rad2.y + 1) * 0.5f);

		// Scale
		rad2.x *= width;
		rad2.y *= height;

		// Shift
		rad2.x += centroid.X;
		rad2.y += centroid.Y;

		// Truncate
		VCPoint p2 (rad2.x, rad2.y);

		// Add verts ( This way is actually faster... I <3 the profiler )
		m_verts[m_vCount].Position.x = (GLshort)centroid.X;		m_verts[m_vCount].Position.y = (GLshort)centroid.Y;		m_verts[m_vCount].Position.z = depthStep;	m_verts[m_vCount++].Color = centroidC;
		m_verts[m_vCount].Position.x = (GLshort)p1.X;			m_verts[m_vCount].Position.y = (GLshort)p1.Y;			m_verts[m_vCount].Position.z = depthStep;	m_verts[m_vCount++].Color = c1;
		m_verts[m_vCount].Position.x = (GLshort)p2.X;			m_verts[m_vCount].Position.y = (GLshort)p2.Y;			m_verts[m_vCount].Position.z = depthStep;	m_verts[m_vCount++].Color = c2;

		p1 = p2;
		c1 = c2;
	}
}

void VCGeometryBuilder::AddQuad( GuiRectVerticie vert, float depthStep )
{
	if (m_vCount >= VC_GEOMETRY_MAX_VERT_SIZE)
	{
		VCLog::Error("You have 125000+ Gui rectangles... too much man.", "Rendering");
	}

	m_verts[m_vCount] = vert;
	m_verts[m_vCount].Position.z = depthStep;
	m_vCount++;
}

void VCGeometryBuilder::Initialize()
{
	// Create a render stage for text rendering
	m_renderStage = new VCRenderStage(VCVoidDelegate::from_method<VCGeometryBuilder, &VCGeometryBuilder::Render>(this));
	m_renderStage->BatchOrder = VC_BATCH_GUI_BASE;
	m_renderStage->Shader = VCResourceManager::GetShaderInResources("Gui");
	m_parentGui->AddGUIRenderStage(m_renderStage);

	m_gpuBuffer = new VCGLBuffer();
	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexAttribute(VCShaderAttribute::Position0,	3, VCGLPrimitives::Short,			false,	sizeof(GuiRectVerticie), offsetof(GuiRectVerticie, Position))
		.SetVertexAttribute(VCShaderAttribute::Color0,		4, VCGLPrimitives::UnsignedByte,	true,	sizeof(GuiRectVerticie), offsetof(GuiRectVerticie, Color));
}

void VCGeometryBuilder::Render()
{
	if (m_vCount == 0)
		return;

	VCGLShader::BoundShader->SetModelMatrix(glm::ortho<float>(0, VCGLWindow::ActiveWindow->Width * m_parentGui->InverseScale, 0, VCGLWindow::ActiveWindow->Height * m_parentGui->InverseScale, -100000, -1));

	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexData(sizeof(GuiRectVerticie) * m_vCount, m_verts, m_vCount, VCGLDrawModes::Stream);

	m_gpuBuffer->Draw();

	m_vCount = 0;
}
