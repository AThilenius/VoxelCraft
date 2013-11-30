//
//  VCVoxelFallbackShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/29/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCVoxelFallbackShader.h"
#include "VCCamera.h"
#include "VCShadowShader.h"

VCVoxelFallbackShader::VCVoxelFallbackShader(void):
	m_unifMVP(-1),
	m_unifViewMatrix(-1),
	m_unifModelMatrix(-1),
	m_unifLightInvDirection(-1)
{
	m_vertexShader = "VoxelFallback";
	m_fragShader = "VoxelFallback";
}

VCVoxelFallbackShader::~VCVoxelFallbackShader(void)
{
}

void VCVoxelFallbackShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	// Create Camera's MVP
	VCCamera* currentCamera = VCShader::BoundCamera;
	glm::mat4 ProjectionMatrix = currentCamera->ProjectionMatrix;
	glm::mat4 ViewMatrix = currentCamera->ViewMatrix;
	glm::mat4 ModelMatrix = modelMatrix;
	glm::mat4 MVP = currentCamera->ProjectionViewMatrix * modelMatrix;

	// Update uniforms
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_unifModelMatrix, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(m_unifViewMatrix, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniform3f(m_unifLightInvDirection, VCShadowShader::LightInverseDirection.x, VCShadowShader::LightInverseDirection.y, VCShadowShader::LightInverseDirection.z);

	glErrorCheck();
}

void VCVoxelFallbackShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_NORMAL, "normal");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");

	glErrorCheck();
}

void VCVoxelFallbackShader::GetUniformIDs()
{
	// Vertex
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
	m_unifViewMatrix = glGetUniformLocation(m_programId, "ViewMatrix");
	m_unifModelMatrix = glGetUniformLocation(m_programId, "ModelMatrix");
	m_unifLightInvDirection = glGetUniformLocation(m_programId, "LightInvDirection_worldspace");
	
	glErrorCheck();
}