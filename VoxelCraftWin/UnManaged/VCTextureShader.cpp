//
//  VCTextureShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTextureShader.h"


VCTextureShader::VCTextureShader(void):
	m_unifTexture(-1)
{
	m_vertexShader = "TexturePassThrough";
	m_fragShader = "TexturePassThrough";
}


VCTextureShader::~VCTextureShader(void)
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
