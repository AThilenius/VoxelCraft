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
#include "VCCamera.h"


VCColorPassThroughShader::VCColorPassThroughShader(void) :
	m_unifMVP(-1)
{
	m_vertexShader = "ColorPassThrough";
	m_fragShader = "ColorPassThrough";
}


VCColorPassThroughShader::~VCColorPassThroughShader(void)
{
}

void VCColorPassThroughShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	glm::mat4 MVP = VCShader::BoundCamera->ProjectionViewMatrix * modelMatrix;
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
