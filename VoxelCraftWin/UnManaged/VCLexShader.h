//
//  VCLexShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "Shader.h"

class VCLexShader : public Shader
{
public:
	VCLexShader(void);
	~VCLexShader(void);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifProjMatrix;
	GLint m_unifGlyphsTex;
};

