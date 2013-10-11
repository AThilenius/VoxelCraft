//
//  VCDebug.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCDebug.h"

int VCDebug::m_lineVertCount = 0;
LineVerticie VCDebug::m_lineVerts[] = {};
GLuint VCDebug::m_VAO = 0;
GLuint VCDebug::m_VBO = 0;

VCDebug::VCDebug(void)
{
}


VCDebug::~VCDebug(void)
{
}

void VCDebug::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Debug::VCInteropDebugReset",		(void*) VCInteropDebugReset);
	mono_add_internal_call("VCEngine.Debug::VCInteropDebugDrawLine",	(void*) VCInteropDebugDrawLine);
	mono_add_internal_call("VCEngine.Debug::VCInteropDebugDrawCube",	(void*) VCInteropDebugDrawCube);
}

void VCInteropDebugReset()
{
	VCDebug::Reset();
}

void VCInteropDebugDrawLine (vec3 from, vec3 to, vcint4 color)
{
	VCDebug::DrawLine(from, to, GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropDebugDrawCube (vec3 corner, vec3 scale, vcint4 color)
{
	VCDebug::DrawCube(corner, scale, GLubyte4(color.X, color.Y, color.Z, color.W));
}