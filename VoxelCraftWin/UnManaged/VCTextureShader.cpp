//
//  VCTextureShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTextureShader.h"

static string g_vcShadVertexShader =
    "#version 150\n"
	
	"in vec3 position;"
	"out vec2 UV;"

	"void main()"
	"{"
		"gl_Position =  vec4(position, 1);"
		"UV = (position.xy + vec2(1, 1)) / 2.0;"
	"}";

static string g_vcShadFragmentShader =
	"#version 150\n"

	"in vec2 UV;"
	"out vec4 color;"
	"uniform sampler2D texture;"

	"void main()"
	"{"
		"color = texture2D(texture, UV);"
	"}";



VCTextureShader::VCTextureShader(void):
	m_unifTexture(-1)
{
	m_vertexShaderLiteral = &g_vcShadVertexShader;
	m_fragShaderLiteral = &g_vcShadFragmentShader;
	m_geometryShaderLiteral = NULL;
}


VCTextureShader::~VCTextureShader(void)
{
}

void VCTextureShader::SetModelMatrix( glm::mat4 modelMatrix )
{
}

void VCTextureShader::SetTextureUnit(GLint tex)
{
	glUniform1i(m_unifTexture, tex);
}

void VCTextureShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
}

void VCTextureShader::GetUniformIDs()
{
	m_unifTexture = glGetUniformLocation(m_programId, "texture");
}

void VCTextureShader::PostInitialize()
{
}
