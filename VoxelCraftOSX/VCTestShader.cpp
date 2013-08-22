//
//  VMTestShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTestShader.h"


static string g_vcVoxVertexShader =
"#version 150\n"

"in vec4 position;"

"void main()"
"{"

    "gl_Position = position;"

"}";

static string g_vcVoxFragmentShader =
"#version 150\n"

"out vec4 colorF;"

"void main()"
"{"
    "colorF = vec4(1,0,0,1);"
"}";

VCTestShader::VCTestShader(void)
{
	m_vertexShaderLiteral = &g_vcVoxVertexShader;
	m_fragShaderLiteral = &g_vcVoxFragmentShader;
	m_geometryShaderLiteral = NULL;
}

VCTestShader::~VCTestShader(void)
{
}

void VCTestShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glErrorCheck();
}

void VCTestShader::GetUniformIDs()
{
}

void VCTestShader::PostInitialize()
{
}