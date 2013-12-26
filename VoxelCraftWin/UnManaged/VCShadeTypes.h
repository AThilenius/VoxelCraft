//
//  VCShaderValues.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "VCResourceManager.h"
#include "VCTexture.h"


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

// =====   Base Class   ======================================================
class VCShaderValue
{
public:
	virtual ~VCShaderValue() {}
	virtual void Set() = 0;
	virtual std::string ToJson() = 0;

public:
	std::string Name;
	GLuint UniformID;
	VCShaderUniform::DataTypes Type;
};

// =====   Float   ======================================================
class VCShaderFloat : public VCShaderValue
{
public:
	VCShaderFloat() { VCShaderValue::Type = VCShaderUniform::Float; }

	virtual void Set() { glUniform1f(UniformID, Value); }

	virtual std::string ToJson() { return std::to_string(Value); }

	static VCShaderFloat* FromJson (std::string name, GLuint unifomID, std::string json)
	{
		VCShaderFloat* f = new VCShaderFloat();
		f->Name = name;
		f->UniformID = unifomID;
		f->Value = atof(json.c_str());
		return f;
	}

public: 
	float Value;
};

// =====   Int   ======================================================
class VCShaderInt : public VCShaderValue
{
public:
	VCShaderInt() { VCShaderValue::Type = VCShaderUniform::Int; }

	virtual void Set() { glUniform1i(UniformID, Value); }

	virtual std::string ToJson() { return std::to_string(Value); }

	static VCShaderInt* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderInt* f = new VCShaderInt();
		f->Name = name;
		f->UniformID = unifomID;
		f->Value = atoi(json.c_str());
		return f;
	}

public: 
	int Value;
};

// =====   Vector2   ======================================================
class VCShaderVector2 : public VCShaderValue
{
public:
	VCShaderVector2() { VCShaderValue::Type = VCShaderUniform::Vector2; }

	virtual void Set() { glUniform2fv(UniformID, 1, &Value[0]); }

	virtual std::string ToJson() { return "{" + std::to_string(Value.x) + ":" + std::to_string(Value.y) +"}"; }

	static VCShaderVector2* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderVector2* f = new VCShaderVector2();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);
		f->Value.x = atof(subStrs[0].c_str());
		f->Value.y = atof(subStrs[1].c_str());
		return f;
	}

public: 
	glm::vec2 Value;
};

// =====   Vector3   ======================================================
class VCShaderVector3 : public VCShaderValue
{
public:
	VCShaderVector3() { VCShaderValue::Type = VCShaderUniform::Vector3; }

	virtual void Set() { glUniform3fv(UniformID, 1, &Value[0]); }

	virtual std::string ToJson() { return "{" + std::to_string(Value.x) + ":" + std::to_string(Value.y) + ":" + std::to_string(Value.z) +"}"; }

	static VCShaderVector3* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderVector3* f = new VCShaderVector3();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);
		f->Value.x = atof(subStrs[0].c_str());
		f->Value.y = atof(subStrs[1].c_str());
		f->Value.z = atof(subStrs[2].c_str());
		return f;
	}

public: 
	glm::vec3 Value;
};

// =====   Vector4   ======================================================
class VCShaderVector4 : public VCShaderValue
{
public:
	VCShaderVector4() { VCShaderValue::Type = VCShaderUniform::Vector4; }

	virtual void Set() { glUniform4fv(UniformID, 1, &Value[0]); }

	virtual std::string ToJson() { return "{" + std::to_string(Value.x) + ":" + std::to_string(Value.y) + ":" + std::to_string(Value.z) + ":" + std::to_string(Value.w) +"}"; }

	static VCShaderVector4* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderVector4* f = new VCShaderVector4();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);
		f->Value.x = atof(subStrs[0].c_str());
		f->Value.y = atof(subStrs[1].c_str());
		f->Value.z = atof(subStrs[2].c_str());
		f->Value.w = atof(subStrs[3].c_str());
		return f;
	}

public: 
	glm::vec4 Value;
};

// =====   Matrix3   ======================================================
class VCShaderMatrix3 : public VCShaderValue
{
public:
	VCShaderMatrix3() { VCShaderValue::Type = VCShaderUniform::Matrix3; }

	virtual void Set() { glUniformMatrix3fv(UniformID, 1, GL_FALSE, &Value[0][0]); }

	virtual std::string ToJson() 
	{
		std::string str("{");

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				str.append(std::to_string(Value[x][y]));

				if (x != 2 && y != 2)
					str.append(":");
			}
		}

		str.append("}");
		return str;
	}

	static VCShaderMatrix3* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderMatrix3* f = new VCShaderMatrix3();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);

		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				f->Value[x][y] = atof(subStrs[x*3 + y].c_str());

		return f;
	}

public: 
	glm::mat3 Value;
};

// =====   Matrix4   ======================================================
class VCShaderMatrix4 : public VCShaderValue
{
public:
	VCShaderMatrix4() { VCShaderValue::Type = VCShaderUniform::Matrix4; }

	virtual void Set() { glUniformMatrix4fv(UniformID, 1, GL_FALSE, &Value[0][0]); }

	virtual std::string ToJson() 
	{
		std::string str("{");

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				str.append(std::to_string(Value[x][y]));

				if (x != 3 && y != 3)
					str.append(":");
			}
		}

		str.append("}");
		return str;
	}

	static VCShaderMatrix4* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderMatrix4* f = new VCShaderMatrix4();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);

		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				f->Value[x][y] = atof(subStrs[x*4 + y].c_str());

		return f;
	}

public: 
	glm::mat4 Value;
};

// =====   ColorRGBA   ======================================================
class VCShaderColorRGBA : public VCShaderValue
{
public:
	VCShaderColorRGBA() { VCShaderValue::Type = VCShaderUniform::ColorRGBA; }

	virtual void Set() { glUniform4f(UniformID, (float)Value.x / 255.0f, (float)Value.y / 255.0f, (float)Value.z / 255.0f, (float)Value.w / 255.0f ); }

	virtual std::string ToJson() { return "{" + std::to_string(Value.x) + ":" + std::to_string(Value.y) + ":" + std::to_string(Value.z) + ":" + std::to_string(Value.w) +"}"; }

	static VCShaderColorRGBA* FromJson (std::string name, GLuint unifomID, std::string json) 
	{
		VCShaderColorRGBA* f = new VCShaderColorRGBA();
		f->Name = name;
		f->UniformID = unifomID;
		std::vector<std::string> subStrs = SplitString(json);
		f->Value.x = atof(subStrs[0].c_str());
		f->Value.y = atof(subStrs[1].c_str());
		f->Value.z = atof(subStrs[2].c_str());
		f->Value.w = atof(subStrs[3].c_str());
		return f;
	}

public: 
	GLubyte4 Value;
};

// =====   Sampler2D   ======================================================
class VCShaderSampler2D : public VCShaderValue
{
public:
	VCShaderSampler2D() { VCShaderValue::Type = VCShaderUniform::Sampler2D; }

	virtual void Set() { Texture->Bind(TexUnit); }

	virtual std::string ToJson() { return Texture->FullPath; }

	static VCShaderSampler2D* FromJson (std::string name, GLuint unifomID, int textUnit, std::string json) 
	{
		VCShaderSampler2D* f = new VCShaderSampler2D();
		f->Name = name;
		f->UniformID = unifomID;
		f->TexUnit = textUnit;
		f->Texture = VCResourceManager::GetTexureInAssets(json);
		return f;
	}

public: 
	int TexUnit;
	VCTexture* Texture;
};

// =====   Sampler3D   ======================================================
class VCShaderSampler3D : public VCShaderValue
{
public:
	VCShaderSampler3D() { VCShaderValue::Type = VCShaderUniform::Sampler3D; }

	virtual void Set() { Texture->Bind(TexUnit); }

	virtual std::string ToJson() { return Texture->FullPath; }

	static VCShaderSampler3D* FromJson (std::string name, GLuint unifomID, int textUnit, std::string json) 
	{
		VCShaderSampler3D* f = new VCShaderSampler3D();
		f->Name = name;
		f->UniformID = unifomID;
		f->TexUnit = textUnit;
		f->Texture = VCResourceManager::GetTexureInAssets(json);
		return f;
	}

public: 
	int TexUnit;
	VCTexture* Texture;
};