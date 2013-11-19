//
//  Shader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCCamera;

// Matrix Multiple Order: Projection * View * Model

class VCShader
{
public:
	VCShader();
	~VCShader();
	void Initialize();
	virtual void Bind(VCCamera* camera);

	virtual void SetModelMatrix(glm::mat4 modelMatrix){}

	static VCShader* BoundShader;
	static VCCamera* BoundCamera;

protected:
	// Use glBindAttribLocation(GLuint program, GLuint name(ID), "attribute name");
	virtual void BindAttribLocations() = 0;

	// NOTE: GLint, not GLuint!
	// Use GLint = glGetUniformLocation(GLuint program, "uniform name");
	virtual void GetUniformIDs() = 0;

	// Use this to bind any uniform defaults
	virtual void PostInitialize() {};

private:
	void CompileShader(GLenum shaderType, GLuint* ShaderId, std::string shaderLiteral);
	void LinkProgram();

protected:
	char *m_vertexShader, *m_fragShader, *m_geometryShader;
	GLuint m_programId;

	friend bool operator==(const VCShader& lhs, const VCShader& rhs);
	friend bool operator< (const VCShader& lhs, const VCShader& rhs);
};

bool operator==(const VCShader& lhs, const VCShader& rhs);
bool operator< (const VCShader& lhs, const VCShader& rhs);
bool operator!=(const VCShader& lhs, const VCShader& rhs);
bool operator> (const VCShader& lhs, const VCShader& rhs);
bool operator<=(const VCShader& lhs, const VCShader& rhs);
bool operator>=(const VCShader& lhs, const VCShader& rhs);

