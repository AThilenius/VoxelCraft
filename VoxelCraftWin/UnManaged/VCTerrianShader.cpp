//
//  VCTerrianShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTerrianShader.h"
#include "VCCamera.h"
#include "VCShadowShader.h"
#include "VCCamera.h"


VCTerrianShader::VCTerrianShader():
	m_unifMVP(0),
	m_unifLightDir(0)
{
	m_vertexShader = "Terrain";
	m_geometryShader = "Terrain";
	m_fragShader = "Terrain";
}

VCTerrianShader::~VCTerrianShader(void)
{
}

void VCTerrianShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	// MVP
	glm::mat4 MVP = Shader::BoundCamera->ProjectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);

	// Light Dir
	glm::vec4 lightInvDirWorld(VCShadowShader::LightInverseDirection.x, VCShadowShader::LightInverseDirection.y, VCShadowShader::LightInverseDirection.z, 1);
	glm::vec4 lightDirCameraSpace = Shader::BoundCamera->ViewMatrix * lightInvDirWorld;

	//"LightDirection_cameraspace = ( ViewMatrix * vec4( LightInvDirection_worldspace, 0 ) ).xyz;"

	glUniform3f(m_unifLightDir, lightDirCameraSpace.x, lightDirCameraSpace.y, lightDirCameraSpace.z);
	glErrorCheck();
}

void VCTerrianShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_FLAGS, "flags");

	glErrorCheck();
}

void VCTerrianShader::GetUniformIDs()
{
	// Vertex
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
	m_unifLightDir = glGetUniformLocation(m_programId, "LightDir");
	glErrorCheck();
}

void VCTerrianShader::PostInitialize()
{
}
