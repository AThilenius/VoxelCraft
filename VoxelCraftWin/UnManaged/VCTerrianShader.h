//
//  VCTerrianShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "Shader.h"

class VCTerrianShader : public Shader
{
public:
	VCTerrianShader();
	~VCTerrianShader(void);

	virtual void SetModelMatrix(glm::mat4 modelMatrix);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifMVP;
};