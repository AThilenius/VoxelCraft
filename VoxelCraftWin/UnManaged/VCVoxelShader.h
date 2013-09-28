//
//  VCVoxelShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "Shader.h"
#include "VCSceneGraph.h"

using namespace std;

class VCVoxelShader : public Shader
{
public:
	VCVoxelShader(GLuint textId);
	~VCVoxelShader(void);

	virtual void SetModelMatrix(glm::mat4 modelMatrix);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLuint m_texID;

	GLint m_unifMVP;
	GLint m_unifViewMatrix;
	GLint m_unifModelMatrix;
	GLint m_unifDepthMVP;
	GLint m_unifLightInvDirection;
	GLint m_unifShadow;
};

