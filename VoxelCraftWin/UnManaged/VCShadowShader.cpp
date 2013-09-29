//
//  VCShadowShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCShadowShader.h"


static string g_vcShadVertexShader =
    "#version 150\n"
	//"#version 330 core\n"

	"in vec4 vertexPosition_modelspace;"
	"uniform mat4 depthMVP;"

	"void main()"
	"{"
		"gl_Position =  depthMVP * vertexPosition_modelspace;"
	"}";

static string g_vcShadFragmentShader =
	"#version 150\n"
	//"#version 330 core\n"

	"out float fragmentdepth;"

	"void main()"
	"{"
		"fragmentdepth = gl_FragCoord.z;"
	"}";


VCShadowShader::VCShadowShader(void)
{
	m_vertexShaderLiteral = &g_vcShadVertexShader;
	m_fragShaderLiteral = &g_vcShadFragmentShader;
	m_geometryShaderLiteral = NULL;

	m_unifMVP = -1;
}


VCShadowShader::~VCShadowShader(void)
{
}

void VCShadowShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>( -30, 30, -30, 30, -100, 100);

	glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
	depthViewMatrix = glm::translate(depthViewMatrix, -15.0f, 0.0f, 0.0f);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix* modelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &depthMVP[0][0]);

	glErrorCheck();
}

void VCShadowShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "vertexPosition_modelspace");

	glErrorCheck();
}

void VCShadowShader::GetUniformIDs()
{
	m_unifMVP = glGetUniformLocation(m_programId, "depthMVP");

	glErrorCheck();
}

void VCShadowShader::PostInitialize()
{
}
