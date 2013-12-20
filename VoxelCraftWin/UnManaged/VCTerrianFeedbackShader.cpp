////
////  VCTerrainFeedback.cpp
////  VoxelCraftOSX
////
////  Created by Alec Thilenius on 11/19/13.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCTerrianFeedbackShader.h"
//#include "VCShadowShader.h"
//#include "VCCamera.h"
//
//
//VCTerrianFeedbackShader::VCTerrianFeedbackShader(void)
//{
//	m_vertexShader = "TerrainFeedback";
//	m_fragShader = "TerrainFeedback";
//}
//
//VCTerrianFeedbackShader::~VCTerrianFeedbackShader(void)
//{
//}
//
//void VCTerrianFeedbackShader::SetModelMatrix( glm::mat4 modelMatrix )
//{
//	// MVP
//	glm::mat4 MVP = VCShader::BoundCamera->ProjectionViewMatrix * modelMatrix;
//
//	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
//
//	// Light Dir
//	glm::vec4 lightInvDirWorld(VCShadowShader::LightInverseDirection.x, VCShadowShader::LightInverseDirection.y, VCShadowShader::LightInverseDirection.z, 1);
//	glm::vec4 lightDirCameraSpace = VCShader::BoundCamera->ViewMatrix * lightInvDirWorld;
//	glm::vec3 normLight = glm::vec3(lightDirCameraSpace.x, lightDirCameraSpace.y, lightDirCameraSpace.z);
//	normLight = glm::normalize(normLight);
//	//glUniform3f(m_unifLightDir, normLight.x, normLight.y, normLight.z);
//
//	glErrorCheck();
//}
//
//void VCTerrianFeedbackShader::BindAttribLocations()
//{
//	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "positionIn");
//	//glBindAttribLocation(m_programId, VC_ATTRIBUTE_NORMAL, "normalIn");
//	//glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "colorIn");
//	
//	glErrorCheck();
//}
//
//void VCTerrianFeedbackShader::GetUniformIDs()
//{
//	// Vertex
//	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
//	//m_unifLightDir = glGetUniformLocation(m_programId, "LightDir");
//	glErrorCheck();
//}
//
//void VCTerrianFeedbackShader::PostInitialize()
//{
//}
