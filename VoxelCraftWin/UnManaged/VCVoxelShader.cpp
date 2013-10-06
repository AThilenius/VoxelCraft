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
	//"#version 330 core\n"

	"in vec4 position;"
	"in int normal;"
	"in vec4 color;"

	"out vec3 Position_worldspace;"
	"out vec3 Normal_cameraspace;"
	"out vec3 LightDirection_cameraspace;"
	"out vec4 ShadowCoord;"
	"out vec4 colorVarying;"

	"uniform mat4 MVP;"
	"uniform mat4 ViewMatrix;"
	"uniform mat4 ModelMatrix;"
	"uniform mat4 DepthBiasMVP;"
	"uniform vec3 LightInvDirection_worldspace;"
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
		"vec3 vertexNormal_modelspace = NormalLookupTable[int(normal)];"
	
		"gl_Position =  MVP * position;"
		"colorVarying = color;"
		"ShadowCoord = DepthBiasMVP * position;"
	
		// Position of the vertex, in worldspace : ModelMatrix * position
		"Position_worldspace = ( ModelMatrix * position ).xyz;"
	
		// Vector that goes from the vertex to the light, in camera space
		"LightDirection_cameraspace = ( ViewMatrix * vec4( LightInvDirection_worldspace, 0 ) ).xyz;"
	
		// Normal of the the vertex, in camera space
		// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
		"Normal_cameraspace = ( ViewMatrix * ModelMatrix * vec4( vertexNormal_modelspace, 0 ) ).xyz;"
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
    "#version 150\n"
	//"#version 330 core\n"

	"in vec3 Position_worldspace;"
	"in vec3 Normal_cameraspace;"
	"in vec3 LightDirection_cameraspace;"
	"in vec4 ShadowCoord;"
	"in vec4 colorVarying;"

	"out vec4 color;"

	"uniform sampler2D shadowMap;"

	"vec2 poissonDisk[16] = vec2[]( "
	   "vec2( -0.94201624, -0.39906216 ), "
	   "vec2( 0.94558609, -0.76890725 ), "
	   "vec2( -0.094184101, -0.92938870 ), "
	   "vec2( 0.34495938, 0.29387760 ), "
	   "vec2( -0.91588581, 0.45771432 ), "
	   "vec2( -0.81544232, -0.87912464 ), "
	   "vec2( -0.38277543, 0.27676845 ), "
	   "vec2( 0.97484398, 0.75648379 ), "
	   "vec2( 0.44323325, -0.97511554 ), "
	   "vec2( 0.53742981, -0.47373420 ), "
	   "vec2( -0.26496911, -0.41893023 ), "
	   "vec2( 0.79197514, 0.19090188 ), "
	   "vec2( -0.24188840, 0.99706507 ), "
	   "vec2( -0.81409955, 0.91437590 ), "
	   "vec2( 0.19984126, 0.78641367 ), "
	   "vec2( 0.14383161, -0.14100790 ) "
	");"

	"float random( vec3 seed, int i )"
	"{"
		"vec4 seed4 = vec4( seed, i );"
		"float dot_product = dot( seed4, vec4( 12.9898, 78.233, 45.164, 94.673 ) );"
		"return fract( sin( dot_product ) * 43758.5453 );"
	"}"

	"void main()"
	"{"
		// Normal of the computed fragment, in camera space
		"vec3 n = normalize( Normal_cameraspace );"

		// Direction of the light (from the fragment to the light)
		"vec3 l = normalize( LightDirection_cameraspace );"

		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendiular to the triangle -> 0
		//  - light is behind the triangle -> 0
		"float cosTheta = clamp( dot( n,l ), 0, 1 );"
	
		"float visibility = 1.0;"
		"float bias = 0.005 * tan( acos( cosTheta ) );"
		"bias = clamp( bias, 0, 0.01 );"

		// Sample the shadow map 4 times
		"for ( int i = 0; i < 4; i++ )"
		"{"

			//  - A random sample, based on the pixel's position in world space.
			//    The position is rounded to the millimeter to avoid too much aliasing
			"int index = int( 16.0 * random( floor( Position_worldspace.xyz * 1000.0 ), i) ) % 16;"
		
			//"visibility -= 0.2 * ( 1.0 - texture( shadowMap, vec3( ShadowCoord.xy + poissonDisk[index] / 700.0,  (ShadowCoord.z - bias) / ShadowCoord.w) ));"

			"if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )"
				"visibility -= 0.2;"

		"}"
	
		"color = "

			// Ambient
			"colorVarying * 0.3 +"
		
			// Lit Diffuse
			"visibility * colorVarying * cosTheta * 0.6;"

		"color.w = colorVarying.w;"

	"}";


// Old Shader:
	//"in vec4 colorVarying;"
	//"out vec4 colorF;"

	//"void main()"
	//"{"
	//	"colorF = colorVarying;"
	//"}";

VCVoxelShader::VCVoxelShader():
	m_unifMVP(0),
	m_unifDepthMVP(0),
	m_unifShadow(0)
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
	glm::mat4 depthMVP = VCShadowShader::DepthVPMatrix * modelMatrix;

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
	glm::mat4 ModelMatrix = modelMatrix;
	glm::mat4 MVP = currentCamera->ProjectionViewMatrix * modelMatrix;

	// Update uniforms
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_unifModelMatrix, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(m_unifViewMatrix, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(m_unifDepthMVP, 1, GL_FALSE, &depthBiasMVP[0][0]);

	glUniform3f(m_unifLightInvDirection, VCShadowShader::LightInverseDirection.x, VCShadowShader::LightInverseDirection.y, VCShadowShader::LightInverseDirection.z);

	glUniform1i(m_unifShadow, 0);

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
	// Vertex
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
	m_unifViewMatrix = glGetUniformLocation(m_programId, "ViewMatrix");
	m_unifModelMatrix = glGetUniformLocation(m_programId, "ModelMatrix");
	m_unifDepthMVP = glGetUniformLocation(m_programId, "DepthBiasMVP");
	m_unifLightInvDirection = glGetUniformLocation(m_programId, "LightInvDirection_worldspace");

	// Fragment
	m_unifShadow = glGetUniformLocation(m_programId, "shadowMap");

	glErrorCheck();
}

void VCVoxelShader::PostInitialize()
{
}
