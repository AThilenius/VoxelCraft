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
	void Bind();

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

