//
//  VCGuiShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGuiShader.h"
#include "VCWindow.h"

static std::string g_vcGuiVertexShader =
	"#version 150\n"
	//"#version 330 core\n"

	"in vec2 Position;"
	"in vec4 Color;"

	"uniform mat4 projMatrix;"

	"out vec4 VaryingColor;"

	"void main()"
	"{"
		"gl_Position =  projMatrix * vec4(Position.x, Position.y, 0, 1);"
		"VaryingColor =  Color;"
	"}";

static std::string g_vcGuiFragmentShader =
	"#version 150\n"
	//"#version 330 core\n"

	"in vec4 VaryingColor;"

	"out vec4 fragColor;"

	"void main()"
	"{"
	"	fragColor = VaryingColor;"
	"}";


VCGuiShader::VCGuiShader(void):
	m_unifProjMatrix(-1)
{
	m_vertexShaderLiteral = &g_vcGuiVertexShader;
	m_fragShaderLiteral = &g_vcGuiFragmentShader;
	m_geometryShaderLiteral = NULL;
}


VCGuiShader::~VCGuiShader(void)
{
}

void VCGuiShader::Bind(VCCamera* camera)
{
	// Takes a null camera
	Shader::Bind(camera);

	// Set Projection Matrix
	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
}


void VCGuiShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "Position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "Color");

	glErrorCheck();
}

void VCGuiShader::GetUniformIDs()
{
	m_unifProjMatrix = glGetUniformLocation(m_programId, "projMatrix");

	glErrorCheck();
}

void VCGuiShader::PostInitialize()
{
	// Set Projection Matrix
	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
}