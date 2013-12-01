//
//  VCTextureShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTexturePassThroughShader.h"
#include "VCCamera.h"
#include "VCWindow.h"


VCTexturePassThroughShader::VCTexturePassThroughShader(void):
	m_unifTexture(-1),
	m_unifMVP(-1)
{
	m_vertexShader = "TexturePassThrough";
	m_fragShader = "TexturePassThrough";
}


VCTexturePassThroughShader::~VCTexturePassThroughShader(void)
{
}

void VCTexturePassThroughShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	glm::mat4 mvp;

	// Accepts a null camera
	if (VCShader::BoundCamera == NULL)
		mvp = modelMatrix;

	else
		mvp = VCShader::BoundCamera->ProjectionViewMatrix * modelMatrix;

	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &mvp[0][0]);
}

void VCTexturePassThroughShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "Position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_TEX_COORD_0, "UV");

	glErrorCheck();
}

void VCTexturePassThroughShader::GetUniformIDs()
{
	m_unifMVP = glGetUniformLocation(m_programId, "projMatrix");
	m_unifTexture = glGetUniformLocation(m_programId, "texture");

	glErrorCheck();
}

void VCTexturePassThroughShader::PostInitialize()
{
	// Set Projection Matrix and Tex unit
	glUniform1i(m_unifTexture, 0);
}