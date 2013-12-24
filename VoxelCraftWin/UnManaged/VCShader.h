//
//  Shader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCCamera;

struct VCShaderAttribute
{
	enum AttributeTypes
	{
		Position0   = 0,
		Position1   = 1,
		Position2   = 2,
		Position3   = 3,
		Position4   = 4,
		Normal0     = 5,
		Normal1     = 6,
		Normal2     = 7,
		Normal3     = 8,
		Normal4     = 9,
		Color0      = 10,
		Color1      = 11,
		Color2      = 12,
		Color3      = 13,
		Color4      = 14,
		TexCoord0   = 15,
		TexCoord1   = 16,
		TexCoord2   = 17,
		TexCoord3   = 18,
		TexCoord4   = 19,
		Flags0      = 20,
		Flags1      = 21,
		Flags2      = 22,
		Flags3      = 23,
		Flags4      = 24
	};

	VCShaderAttribute(int id, std::string name);
	~VCShaderAttribute(void);
	int ID;
	std::string Name;

	// Runtime Lookup
	static char* RuntimeLookup[25];
	static int GetID (std::string& name);
};

struct VCShaderUniform
{
	enum DataTypes
	{
		Float       = 0,
		Int         = 1,
		Vector2     = 2,
		Vector3     = 3,
		Vector4     = 4,
		Matrix3     = 5,
		Matrix4     = 6,
		ColorRGBA   = 7,
		Sampler2D   = 8,
		Sampler3D   = 9
	};

	VCShaderUniform(int typeId, std::string name);
	~VCShaderUniform(void);

	GLint OpenGlID;
	int TypeID;
	std::string Name;

	// Runtime Lookup
	static char* RuntimeLookup[10];
	static int GetID (std::string& name);
};

#include "VCMarshalableObject.h"

// Matrix Multiple Order: Projection * View * Model
class VCShader : public VCMarshalableObject
{
public:
	VCShader();
	~VCShader();

	static VCShader* GetShader(std::string name);

	void Bind();
	void Compile();
	void SetMVP(glm::mat4 mvp);

	void SetUniform(int index, int value);
	void SetUniform(int index, float value);
	void SetUniform(int index, glm::vec2 value);
	void SetUniform(int index, glm::vec3 value);
	void SetUniform(int index, glm::vec4 value);
	void SetUniform(int index, glm::mat3 value);
	void SetUniform(int index, glm::mat4 value);

	GLint GetUniformIndex(std::string name);

private:

	void BindAttribLocations();
	void GetUniformIDs();
	void PreLink();

	void CompileShader(GLenum shaderType, GLuint* ShaderId, std::string shaderLiteral);
	void LinkProgram();

protected:
	GLuint m_programId;

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
