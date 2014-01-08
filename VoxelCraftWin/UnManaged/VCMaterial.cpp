//
//  VCMaterial.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMaterial.h"

#include "VCPathUtilities.h"
#include <json\json.h>
#include "VCShadeTypes.h"
#include "VCShader.h"

std::unordered_map<std::string, VCMaterial*> VCMaterial::m_loadedMaterial;

VCMaterial::VCMaterial(void)
{
}

VCMaterial::~VCMaterial(void)
{
	for (int i = 0; i < Values.size(); i++)
		delete Values[i];
}

void VCMaterial::Bind(VCCamera* camera)
{
	// Will auto-rebind test.
	Shader->Bind(camera);

	// Set each Uniform's value (Can cull duplicates later)
	for (int i = 0; i < Values.size(); i++)
		Values[i]->Set();
}

VCMaterial* VCMaterial::GetMaterial( std::string fullPath )
{
	auto iter = m_loadedMaterial.find(fullPath);

	if (iter != m_loadedMaterial.end())
		return iter->second;

	// Load a new Material
	std::string materialJson = LoadTextFile(fullPath);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( materialJson, root );

	if ( !parsingSuccessful )
	{
		VC_ERROR("Failed to parse material JSON file: " << fullPath);
	}

	VCMaterial* mat = new VCMaterial();

	// Name
	mat->Name = root.get("Name", "").asString();

	// Shader
	mat->Shader = VCResourceManager::GetShader(root.get("Shader", "").asString());

	// Values
	const Json::Value values = root["UniformValues"];
	int currentTexUnit = 0;
	for ( int i = 0; i < values.size(); i++ )
	{
		std::string valueType = values[i].get("Type", "").asString();
		std::string valueName = values[i].get("Name", "").asString();
		std::string valueData = values[i].get("Value", "").asString();

		int typeID = VCShaderUniform::GetID(valueType);
		VCShaderValue* uniformValue;

		switch (typeID)
		{
			case VCShaderUniform::Float:		uniformValue = VCShaderFloat::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Int:			uniformValue = VCShaderInt::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Vector2:		uniformValue = VCShaderVector2::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Vector3:		uniformValue = VCShaderVector3::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Vector4:		uniformValue = VCShaderVector4::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Matrix3:		uniformValue = VCShaderMatrix3::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Matrix4:		uniformValue = VCShaderMatrix4::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::ColorRGBA:	uniformValue = VCShaderColorRGBA::FromJson(valueName, mat->Shader->GetUniformID(valueName), valueData); break;
			case VCShaderUniform::Sampler2D:	uniformValue = VCShaderSampler2D::FromJson(valueName, mat->Shader->GetUniformID(valueName), GL_TEXTURE0 + currentTexUnit++, valueData); break;
			case VCShaderUniform::Sampler3D:	uniformValue = VCShaderSampler3D::FromJson(valueName, mat->Shader->GetUniformID(valueName), GL_TEXTURE0 + currentTexUnit++, valueData); break;
			default: throw std::exception("Unhanded VCShaderUniform value type");
		}

		mat->Values.push_back(uniformValue);
	}

	m_loadedMaterial.insert(std::unordered_map<std::string, VCMaterial*>::value_type(fullPath, mat));

	return mat;
}