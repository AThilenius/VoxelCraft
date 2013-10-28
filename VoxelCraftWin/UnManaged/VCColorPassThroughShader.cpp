//
//  VCColorPassThroughShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCColorPassThroughShader.h"
#include "VCSceneGraph.h"


static std::string g_vcPTVertexShader =
	"#version 150\n"

	"in vec4 Position;"
	"in vec4 Color;"

	"uniform mat4 MVP;"

	"out vec4 ColorVarying;"

	"void main()"
	"{"
		"gl_Position =  MVP * Position;"
		"ColorVarying = Color;"
	"}";

static std::string g_vcPTFragmentShader =
	"#version 150\n"

	"in vec4 ColorVarying;"
	"out vec4 FragColor;"

	"void main()"
	"{"
		"FragColor = ColorVarying;"
	"}";


VCColorPassThroughShader::VCColorPassThroughShader(void) :
	m_unifMVP(-1)
{
	m_vertexShaderLiteral = &g_vcPTVertexShader;
	m_fragShaderLiteral = &g_vcPTFragmentShader;
	m_geometryShaderLiteral = NULL;
}


VCColorPassThroughShader::~VCColorPassThroughShader(void)
{
}

void VCColorPassThroughShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	glm::mat4 MVP = VCSceneGraph::Instance->CurrentRenderingCamera->ProjectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
	glErrorCheck();
}

void VCColorPassThroughShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "Position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "Color");

	glErrorCheck();
}

void VCColorPassThroughShader::GetUniformIDs()
{
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");

	glErrorCheck();
}

void VCColorPassThroughShader::PostInitialize()
{
}
