//
//  Shader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

using namespace std;

// Matrix Multiple Order: Projection * View * Model

class Shader
{
public:
	Shader();
	~Shader();
	void Initialize();
	virtual void Bind();

	virtual void SetModelMatrix(glm::mat4 modelMatrix){}

	static Shader* BoundShader;

protected:
	// Use glBindAttribLocation(GLuint program, GLuint name(ID), "attribute name");
	virtual void BindAttribLocations() = 0;

	// NOTE: GLint, not GLuint!
	// Use GLint = glGetUniformLocation(GLuint program, "uniform name");
	virtual void GetUniformIDs() = 0;

	// Use this to bind any uniform defaults
	virtual void PostInitialize() {};

private:
	void CompileShader(GLenum shaderType, GLuint* ShaderId, string* shaderLiteral);
	void LinkProgram();

protected:
	string *m_vertexShaderLiteral, *m_fragShaderLiteral, *m_geometryShaderLiteral;
	GLuint m_programId;

};
