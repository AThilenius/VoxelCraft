//
//  VCColorPassThroughShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "Shader.h"

class VCColorPassThroughShader : public Shader
{
public:
	VCColorPassThroughShader(void);
	~VCColorPassThroughShader(void);

	virtual void SetModelMatrix(glm::mat4 modelMatrix);

	static glm::vec3 LightInverseDirection;
	static glm::mat4 DepthVPMatrix;

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifMVP;
};

