//
//  VCTextureShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "shader.h"

class VCTextureShader : public Shader
{
public:
	VCTextureShader(void);
	~VCTextureShader(void);

	virtual void SetModelMatrix(glm::mat4 modelMatrix);
	void SetTextureUnit(GLint tex);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifTexture;
};

