//
//  VCTerrianShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTerrianShader.h"
#include "VCCamera.h"


static std::string g_vcVoxVertexShader =
	"#version 150\n"

	"in vec4 position;"
	"in vec3 color;"
	"in int flags;"

	"out VSOutput"
	"{"
		"vec3 color;"
		"int flags;"
	"} vs_out;"

	"void main()"
	"{"
		"gl_Position =  position;"
		"vs_out.color = color;"
		"vs_out.flags = flags;"
	"}";

static std::string g_vcVoxGeometryShader =
	"#version 150\n"

	//points
	//line_strip
	//triangle_strip
	"layout(points) in;"
	"layout(triangle_strip, max_vertices = 24) out;"

	// input
	"in VSOutput"
	"{"
		"vec3 color;"
		"int flags;"
	"} vs_out[];"

	// output
	"out GSOutput"
	"{"
		"vec3 color;"
		"vec3 normal;"
	"} gs_out;"

	"uniform mat4 MVP;"

	"void main()"
	"{"
		"float cubeScale = 1.0;"

		"vec4 centerPos = gl_in[0].gl_Position;"

		// throw away off-screen cubes to save some performance
		"vec4 centerNDCPos = MVP * centerPos;"
		"if (centerNDCPos.x < -centerNDCPos.w"
			"|| centerNDCPos.x > centerNDCPos.w"
			"|| centerNDCPos.y < -centerNDCPos.w"
			"|| centerNDCPos.y > centerNDCPos.w"
			"|| centerNDCPos.z < -centerNDCPos.w"
			"|| centerNDCPos.z > centerNDCPos.w)"
			"return;"

		// -X
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// +X
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"
			
			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// -Y
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// +Y
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// -Z
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, -.5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// +Z
		"{"
			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, -.5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + cubeScale * vec4(-.5, .5, .5, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
	"}";


static std::string g_vcVoxFragmentShader =
	"#version 150\n"

	"in GSOutput"
	"{"
		"vec3 color;"
		"vec3 normal;"
	"} gs_out;"

	"out vec4 color;"
	
	"void main()"
	"{"
		"color.xyz = gs_out.color;"
		"color.w = 1;"
	"}";

VCTerrianShader::VCTerrianShader():
	m_unifMVP(0)
{
	m_vertexShaderLiteral = &g_vcVoxVertexShader;
	m_geometryShaderLiteral = &g_vcVoxGeometryShader;
	m_fragShaderLiteral = &g_vcVoxFragmentShader;
}

VCTerrianShader::~VCTerrianShader(void)
{
}

void VCTerrianShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	glm::mat4 MVP = Shader::BoundCamera->ProjectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);
	glErrorCheck();
}

void VCTerrianShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_NORMAL, "flags");

	glErrorCheck();
}

void VCTerrianShader::GetUniformIDs()
{
	// Vertex
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
	glErrorCheck();
}

void VCTerrianShader::PostInitialize()
{
}
