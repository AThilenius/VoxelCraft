//
//  VCVoxelShader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCVoxelShader.h"
#include "VCGLRenderer.h"


static string g_vcVoxVertexShader =
    "#version 150\n"

	"in vec4 position;"
	"in int normal;"
	"in vec4 color;"
	
	"uniform mat4 modelViewProjectionMatrix;"
	"uniform mat3 normalMatrix;"
	"uniform vec3 lightPos;"

	"out vec4 colorVarying;"
    
	"uniform vec3 NormalLookupTable[6] = vec3[6] ("
		"vec3(-1.0, 0.0, 0.0),"
		"vec3(1.0, 0.0, 0.0),"
		"vec3(0.0, -1.0, 0.0),"
		"vec3(0.0, 1.0, 0.0),"
		"vec3(0.0, 0.0, -1.0),"
		"vec3(0.0, 0.0, 1.0)"
	");"

	"void main()"
	"{"
		"vec3 normalVal = NormalLookupTable[int(normal)];"
		"vec3 eyeNormal = normalize(normalMatrix * normalVal);"

		"float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPos)));"

		"colorVarying.xyz = color.xyz;" //* nDotVP;"
		"colorVarying.w = color.w;"

		"gl_Position = modelViewProjectionMatrix * position;"
	"}";

static string g_vcVoxFragmentShader =
    "#version 150\n"

    "in vec4 colorVarying;"
    "out vec4 colorF;"

	"void main()"
	"{"
		"colorF = colorVarying;"
	"}";

VCVoxelShader::VCVoxelShader(void)
{
	m_vertexShaderLiteral = &g_vcVoxVertexShader;
	m_fragShaderLiteral = &g_vcVoxFragmentShader;
	m_geometryShaderLiteral = NULL;

	m_unifMVP = -1;
	m_unifNormal = -1;
}

VCVoxelShader::~VCVoxelShader(void)
{
}

void VCVoxelShader::SetModelMatrix( glm::mat4 modelMatrix )
{
    VCCamera* currentCamera = VCSceneGraph::Instance->CurrentRenderingCamera;
	//glm::mat4 viewModel = currentCamera->ViewMatrix * modelMatrix;
	glm::mat4 modelViewProj = currentCamera->ProjectionMatrix * currentCamera->ViewMatrix;// * modelMatrix;
	//glm::mat3 normal = glm::inverseTranspose(glm::mat3(viewModel));

	glUniformMatrix4fv(m_unifMVP, 1, 0, (GLfloat*) &modelViewProj);
	//glUniformMatrix3fv(m_unifNormal, 1, 0, (GLfloat*) &normal);

	glErrorCheck();
}

void VCVoxelShader::SetLightPosition( glm::vec3 position )
{
	glUniform3f(m_unifLightPos, position.x, position.y, position.z);

	glErrorCheck();
}

void VCVoxelShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_NORMAL, "normal");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");

	glErrorCheck();
}

void VCVoxelShader::GetUniformIDs()
{
	m_unifMVP = glGetUniformLocation(m_programId, "modelViewProjectionMatrix");
	//m_unifNormal = glGetUniformLocation(m_programId, "normalMatrix");
	m_unifLightPos = glGetUniformLocation(m_programId, "lightPos");

	glErrorCheck();
}

void VCVoxelShader::PostInitialize()
{
    mat4 identity;
	glUniformMatrix4fv(m_unifMVP, 1, 0, (GLfloat*) &identity);
	SetLightPosition(glm::vec3(1.0f, 1.0f, 100.0f));
}
