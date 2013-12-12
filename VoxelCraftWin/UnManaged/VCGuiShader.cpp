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


VCGuiShader::VCGuiShader(void):
	m_unifProjMatrix(-1)
{
	m_vertexShader = "Gui";
	m_fragShader = "Gui";
}


VCGuiShader::~VCGuiShader(void)
{
}

void VCGuiShader::Bind(VCCamera* camera)
{
	// Takes a null camera
	VCShader::Bind(camera);

	// Set Projection Matrix
	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void VCGuiShader::SetNoise( float level )
{
	glUniform1f(m_unifNoiseScaler, level);
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
	m_unifNoiseScaler = glGetUniformLocation(m_programId, "NoiseScaler");
	
	glErrorCheck();
}

void VCGuiShader::PostInitialize()
{
	// Set Projection Matrix
	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -1, 1);
	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
	//glUniform1f(m_unifNoiseScaler, 0.025f);
	glUniform1f(m_unifNoiseScaler, 0.0f);
}