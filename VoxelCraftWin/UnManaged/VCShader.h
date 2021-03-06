//
//  Shader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define VC_GLSL_VERSION 150

class VCCamera;

#include "VCMarshalableObject.h"
#include "VCShadeTypes.h"

// Matrix Multiple Order: Projection * View * Model
class VCShader : public VCMarshalableObject
{
public:
	VCShader();
	~VCShader();

	void Bind();
	void SetCamera(VCCamera* camera);
	void SetModelMatrix(glm::mat4 modelMatrix);
	void Compile();

	void SetUniform(int index, int value);
	void SetUniform(int index, float value);
	void SetUniform(int index, glm::vec2 value);
	void SetUniform(int index, glm::vec3 value);
	void SetUniform(int index, glm::vec4 value);
	void SetUniform(int index, glm::mat3 value);
	void SetUniform(int index, glm::mat4 value);

	int GetUniformIndex(std::string name);
	GLuint GetUniformID(std::string name);

private:

	static VCShader* GetShader(std::string name);

	void BindAttribLocations();
	void GetUniformIDs();
	void PreLink();

	void CompileShader(GLenum shaderType, GLuint* ShaderId, std::string shaderLiteral);
	void LinkProgram();

protected:
	GLuint m_programId;

	// VC Uniform IDs:
	GLuint m_unifMvpMatrix;
	GLuint m_unifModelMatrix;
	GLuint m_unifViewMatrix;
	GLuint m_unifProjectionMatrix;
	GLuint m_unifLightInverseDirection;

	// VC Uniform Values
	glm::mat4 m_mvpMatrix;
	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_lightInverseDirection;

	// Camera tracking
	VCCamera* m_boundCamera;

	friend class VCRenderStage;
	friend bool operator==(const VCShader& lhs, const VCShader& rhs);
	friend bool operator< (const VCShader& lhs, const VCShader& rhs);

public:
	static VCShader* BoundShader;
	static std::unordered_map<std::string, VCShader*> LoadedShaders;

	std::string Name;
	std::vector<VCShaderAttribute> Attributes;
	std::vector<VCShaderUniform> Uniforms;

	std::string VertexShader;
	std::string GeometryShader;
	std::string FragmentShader;


private:
	DISALLOW_COPY_AND_ASSIGN(VCShader);
	friend class VCResourceManager;
};

bool operator==(const VCShader& lhs, const VCShader& rhs);
bool operator< (const VCShader& lhs, const VCShader& rhs);
bool operator!=(const VCShader& lhs, const VCShader& rhs);
bool operator> (const VCShader& lhs, const VCShader& rhs);
bool operator<=(const VCShader& lhs, const VCShader& rhs);
bool operator>=(const VCShader& lhs, const VCShader& rhs);

DLL_EXPORT_API int VCInteropGetShaderFromFile(char* name);

DLL_EXPORT_API void VCInteropShaderSetUniformInt(int handle, int index, int value);
DLL_EXPORT_API void VCInteropShaderSetUniformFloat(int handle, int index, float value);
DLL_EXPORT_API void VCInteropShaderSetUniformVec2(int handle, int index, glm::vec2 value);
DLL_EXPORT_API void VCInteropShaderSetUniformVec3(int handle, int index, glm::vec3 value);
DLL_EXPORT_API void VCInteropShaderSetUniformVec4(int handle, int index, glm::vec4 value);
DLL_EXPORT_API void VCInteropShaderSetUniformMat3(int handle, int index, glm::mat3 value);
DLL_EXPORT_API void VCInteropShaderSetUniformMat4(int handle, int index, glm::mat4 value);
