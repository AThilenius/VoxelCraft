//
//  VCGuiShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "Shader.h"

class VCGuiShader : public Shader
{
public:
	VCGuiShader(void);
	~VCGuiShader(void);

protected:
	virtual void Bind();
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifProjMatrix;
};


