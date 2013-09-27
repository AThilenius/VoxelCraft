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
    //"#version 150\n"
	"#version 330 core\n"

	"in vec3 position;"
	"in int normal;"
	"in vec4 color;"

	"out vec4 colorVarying;"
	"out vec4 ShadowCoord;"

	"uniform mat4 modelViewProjectionMatrix;"
	"uniform mat4 DepthBiasMVP;"

	"void main()"
	"{"
		"gl_Position =  modelViewProjectionMatrix * vec4(position, 1);"
		"ShadowCoord = DepthBiasMVP * vec4(position, 1);"
		"colorVarying = color;"
	"}";


// Old Shader:
	//"in vec4 position;"
	//"in int normal;"
	//"in vec4 color;"
	//
	//"uniform mat4 modelViewProjectionMatrix;"
	//"uniform mat3 normalMatrix;"
	//"uniform vec3 lightPos;"
	//"uniform vec3 NormalLookupTable[6] = vec3[6] ("
	//	"vec3(-1.0, 0.0, 0.0),"
	//	"vec3(1.0, 0.0, 0.0),"
	//	"vec3(0.0, -1.0, 0.0),"
	//	"vec3(0.0, 1.0, 0.0),"
	//	"vec3(0.0, 0.0, -1.0),"
	//	"vec3(0.0, 0.0, 1.0)"
	//");"

	//"out vec4 colorVarying;"


	//"void main()"
	//"{"
	//	"vec3 normalVal = NormalLookupTable[int(normal)];"
	//	"vec3 eyeNormal = normalize(normalMatrix * normalVal);"

	//	"float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPos)));"

	//	"colorVarying.xyz = (color.xyz * 0.4) + (color.xyz * nDotVP * 0.2);"
	//	"colorVarying.w = color.w;"

	//	"gl_Position = modelViewProjectionMatrix * position;"
	//"}"

static string g_vcVoxFragmentShader =
    //"#version 150\n"
	"#version 330 core\n"

	"in vec4 colorVarying;"
	"in vec4 ShadowCoord;"

	"out vec4 color;"

	"uniform sampler2DShadow  shadowMap;"

	"void main()"
	"{"
		"float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );"
		"float bias = 0.005;"

		"color.xyz = colorVarying.xyz * visibility;"
		"color.w = colorVarying.w;"
	"}";


// Old Shader:
	//"in vec4 colorVarying;"
	//"out vec4 colorF;"

	//"void main()"
	//"{"
	//	"colorF = colorVarying;"
	//"}";

VCVoxelShader::VCVoxelShader(GLuint textId):
	m_unifMVP(0),
	m_unifDepthMVP(0),
	m_unifShadow(0),
	m_texID(textId)
{
	m_vertexShaderLiteral = &g_vcVoxVertexShader;
	m_fragShaderLiteral = &g_vcVoxFragmentShader;
	m_geometryShaderLiteral = NULL;
}

VCVoxelShader::~VCVoxelShader(void)
{
}

void VCVoxelShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	// Re-create the exact same MVP matrix that was used for the shadow pass
	glm::mat4 depthProjectionMatrix = glm::ortho<float>( -30, 30, -30, 30, -100, 100);
	glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(0.5f, 2, 2), glm::vec3(0,0,0), glm::vec3(0,1,0));
	depthViewMatrix = glm::translate(depthViewMatrix, -15.0f, 0.0f, 0.0f);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * modelMatrix;

	// Multiply it be the bias matrix
	glm::mat4 biasMatrix
	(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	
	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;

	// Create Camera's MVP
    VCCamera* currentCamera = VCSceneGraph::Instance->CurrentRenderingCamera;
	glm::mat4 ProjectionMatrix = currentCamera->ProjectionMatrix;
	glm::mat4 ViewMatrix = currentCamera->ViewMatrix;
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * modelMatrix;

	// Update uniforms
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_unifDepthMVP, 1, GL_FALSE, &depthBiasMVP[0][0]);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glUniform1i(m_unifShadow, 0);

	glErrorCheck();
}

void VCVoxelShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	//glBindAttribLocation(m_programId, VC_ATTRIBUTE_NORMAL, "normal");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");

	glErrorCheck();
}

void VCVoxelShader::GetUniformIDs()
{
	m_unifMVP = glGetUniformLocation(m_programId, "modelViewProjectionMatrix");
	m_unifDepthMVP = glGetUniformLocation(m_programId, "DepthBiasMVP");
	m_unifShadow = glGetUniformLocation(m_programId, "shadowMap");

	glErrorCheck();
}

void VCVoxelShader::PostInitialize()
{
}
