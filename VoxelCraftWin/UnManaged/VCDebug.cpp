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