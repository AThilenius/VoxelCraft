//
//  VCLexShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCLexShader.h"

#include "VCWindow.h"

static string g_vcLexVertexShader =
    "#version 150\n"
	//"#version 330 core\n"

	"in vec4 Position;"
	"in vec2 UV;"
	"in vec4 Color;"

	"uniform mat4 projMatrix;"

	"out vec2 VaryingUV;"
	"out vec4 VaryingColor;"

	"void main()"
	"{"
		"gl_Position =  projMatrix * Position;"
		"VaryingUV =  UV;"
		"VaryingColor =  Color;"
	"}";

static string g_vcLexFragmentShader =
	"#version 150\n"
	//"#version 330 core\n"

	"in vec2 VaryingUV;"
	"in vec4 VaryingColor;"

	"uniform sampler2D glyphs;"

	"out vec4 fragColor;"

	"void main()"
	"{"
		"vec4 tcolor = texture2D(glyphs, VaryingUV);"
		"float alpha = 1.0 - (tcolor.x );"
		"fragColor.xyz = VaryingColor.xyz;"
		"fragColor.w = alpha;"
	"}";


VCLexShader::VCLexShader(void):
	m_unifProjMatrix(-1),
	m_unifGlyphsTex(-1)
{
	m_vertexShaderLiteral = &g_vcLexVertexShader;
	m_fragShaderLiteral = &g_vcLexFragmentShader;
	m_geometryShaderLiteral = NULL;
}


VCLexShader::~VCLexShader(void)
{
}

void VCLexShader::Bind()
{
	Shader::Bind();

	// Set Projection Matrix and Tex unit
	mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
}


void VCLexShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "Position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_TEX_COORD_0, "UV");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "Color");

	glErrorCheck();
}

void VCLexShader::GetUniformIDs()
{
	m_unifProjMatrix = glGetUniformLocation(m_programId, "projMatrix");
	m_unifGlyphsTex = glGetUniformLocation(m_programId, "glyphs");

	glErrorCheck();
}

void VCLexShader::PostInitialize()
{
	// Set Projection Matrix and Tex unit
	mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);

	glUniform1i(m_unifGlyphsTex, 0);
}