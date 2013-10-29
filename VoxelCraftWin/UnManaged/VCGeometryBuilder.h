//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCIRenderable.h"

// 1.00 MB
#define VC_GEOMETRY_MAX_VERT_SIZE 256000
#define VC_GEOMETRY_RESOLUTION 36

struct GuiRectVerticie
{
	GuiRectVerticie();
	GuiRectVerticie(GLushort2 position, GLubyte4 color);
	~GuiRectVerticie();

	GLushort2 Position;
	GLubyte4 Color;
};

class VCGeometryBuilder : public VCIRenderable
{
public:
	VCGeometryBuilder(void);
	~VCGeometryBuilder(void);

	void DrawRectangle ( VCRectangle frame, GLubyte4 color );
	void DrawEllipse ( VCPoint centroid, int width, int height, GLubyte4 color );
	void AddQuad( GuiRectVerticie vert );

	void Reset();
	void Initialize();

	virtual VCRenderState* GetState();
	virtual void Render();


private:
	VCRenderState* RenderState;

	GLuint m_VAO;
	GLuint m_VBO;
	int m_vCount;
	GuiRectVerticie m_verts[VC_GEOMETRY_MAX_VERT_SIZE];
	glm::vec2 m_unitCircle[VC_GEOMETRY_RESOLUTION];
};

