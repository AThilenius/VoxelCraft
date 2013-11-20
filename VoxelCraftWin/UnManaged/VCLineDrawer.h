//
//  VCLineDrawer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/11/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCRenderStage;

#include "VCGLRenderer.h"

#define MAX_LINE_COUNT 1000000

struct LineVerticie
{
	LineVerticie();
	LineVerticie(glm::vec3 position, GLubyte4 color);

	GLfloat3 Position;
	GLubyte4 Color;
};

class VCLineDrawer
{
public:
	VCLineDrawer(void);
	~VCLineDrawer(void);

	void Initialize();

	void DrawLine (glm::vec3 from, glm::vec3 to, GLubyte4 color);
	void DrawCube (glm::vec3 corner, glm::vec3 scale, GLubyte4 color);

private:
	void Render();

private:
	VCRenderStage* m_renderStage;
	bool m_warningIssued;
	int m_lineVertCount;
	GLuint m_VAO;
	GLuint m_VBO;
	LineVerticie m_lineVerts[MAX_LINE_COUNT];
};

// Move to VCCamera
void VCInteropDebugDrawLine (glm::vec3 from, glm::vec3 to, vcint4 color);
void VCInteropDebugDrawCube (glm::vec3 corner, glm::vec3 scale, vcint4 color);