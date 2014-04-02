//
//  VCShaderValues.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCShadeTypes.h"

char* VCShaderAttribute::RuntimeLookup[25] = {
	"Position0",
	"Position1",
	"Normal0",
	"Normal1",
	"Color0",
	"Color1",
	"TexCoord0",
	"TexCoord1",
	"Flags0",
	"Flags1",
	"Tangent0",
	"Tangent1",
	"BiTangent0",
	"BiTangent1"
};

char* VCShaderUniform::RuntimeLookup[10] = {
	"Float",
	"Int",
	"Vector2",
	"Vector3",
	"Vector4",
	"Matrix3",
	"Matrix4",
	"ColorRGBA",
	"Sampler2D",
	"Sampler3D"
};

VCShaderAttribute::VCShaderAttribute(int id, std::string name):
	ID(id),
	Name(name)
{
}


VCShaderAttribute::~VCShaderAttribute(void)
{
}

int VCShaderAttribute::GetID( std::string& name )
{
	for(int i = 0; i < 25; i++)
		if (RuntimeLookup[i] == name)
			return i;

	return -1;
}

VCShaderUniform::VCShaderUniform(int typeId, std::string name):
	TypeID(typeId),
	Name(name)
{
}


VCShaderUniform::~VCShaderUniform(void)
{
}

int VCShaderUniform::GetID( std::string& name )
{
	for(int i = 0; i < 10; i++)
	{
		if (RuntimeLookup[i] == name)
			return i;
	}

	return -1;
}