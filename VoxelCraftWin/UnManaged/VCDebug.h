//
//  VCDebug.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCGLRenderer.h"

#define MAX_LINE_COUNT 1000000

struct LineVerticie
{
	LineVerticie();
	LineVerticie(glm::vec3 position, GLubyte4 color);

	GLfloat3 Position;
	GLubyte4 Color;
};

class VCDebug
{
public:
	VCDebug(void);
	~VCDebug(void);

	void Initialize();

	static void DrawLine (glm::vec3 from, glm::vec3 to, GLubyte4 color);
	static void DrawCube (glm::vec3 corner, glm::vec3 scale, GLubyte4 color);

private:
	void Render();


private:
	static bool m_warningIssued;
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