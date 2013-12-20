////
////  VCShadowShader.cpp
////  VoxelCraftOSX
////
////  Created by Alec Thilenius on 9/25/13.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCShadowShader.h"
//#include "VCCamera.h"
//
//glm::vec3 VCShadowShader::LightInverseDirection;
//glm::mat4 VCShadowShader::DepthVPMatrix;
//
//
//VCShadowShader::VCShadowShader(void):
//	m_unifMVP(-1)
//{
//	m_vertexShader = "ShadowZBuffer";
//	m_fragShader = "ShadowZBuffer";
//	VCShadowShader::LightInverseDirection = glm::normalize(glm::vec3(1, 2, 1));
//}
//
//
//VCShadowShader::~VCShadowShader(void)
//{
//}
//
//void VCShadowShader::SetModelMatrix( glm::mat4 modelMatrix )
//{
//	// Compute the MVP matrix from the light's point of view
//	//glm::mat4 depthProjectionMatrix = glm::ortho<float>( -50, 50, -50, 50, -50, 0);
//	//VCShadowShader::LightInverseDirection = glm::normalize(glm::vec3(1, 2, 1));
//	//glm::mat4 depthViewMatrix = glm::lookAt(VCShadowShader::LightInverseDirection, glm::vec3(0,0,0), glm::vec3(0,1,0));
//	//depthViewMatrix = glm::translate(depthViewMatrix, -16.0f, 0.0f, -16.0f);
//	//VCShadowShader::DepthVPMatrix = depthProjectionMatrix * depthViewMatrix;
//
//
//	//// Compute the MVP matrix from the light's point of view
//	glm::mat4 depthProjectionMatrix = glm::ortho<float>( -5, 5, -5, 5, -50, 50);
//	glm::mat4 depthViewMatrix = glm::lookAt(VCShadowShader::LightInverseDirection, glm::vec3(0,0,0), glm::vec3(0,1,0));
//	//depthViewMatrix = glm::translate(depthViewMatrix, -16.0f, 0.0f, -16.0f);
//	depthViewMatrix = glm::translate(depthViewMatrix, glm::vec3( VCShader::BoundCamera->Position.x, 0, VCShader::BoundCamera->Position.z));
//	VCShadowShader::DepthVPMatrix = depthProjectionMatrix * depthViewMatrix;
//
//	glm::mat4 depthMVP = VCShadowShader::DepthVPMatrix * modelMatrix;
//	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &depthMVP[0][0]);
//	glErrorCheck();
//}
//
//void VCShadowShader::BindAttribLocations()
//{
//	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "vertexPosition_modelspace");
//
//	glErrorCheck();
//}
//
//void VCShadowShader::GetUniformIDs()
//{
//	m_unifMVP = glGetUniformLocation(m_programId, "depthMVP");
//
//	glErrorCheck();
//}
//
//void VCShadowShader::PostInitialize()
//{
//}
