//
//  VCShadowShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "Shader.h"

class VCShadowShader : public Shader
{
public:
	VCShadowShader(void);
	~VCShadowShader(void);

	virtual void SetModelMatrix(glm::mat4 modelMatrix);

	static vec3 LightInverseDirection;
	static mat4 DepthVPMatrix;

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifMVP;
};

