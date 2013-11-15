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
#include "VCShadowShader.h"
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
	"layout(triangle_strip, max_vertices = 20) out;"

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
		"vec4 centerPos = gl_in[0].gl_Position;"
		"vec3 shadowVal = vec3(.1, .1, .1);"

		// throw away off-screen cubes to save some performance
		"vec4 centerNDCPos = MVP * centerPos;"
		/*"if (centerNDCPos.x < -centerNDCPos.w"
			"|| centerNDCPos.x > centerNDCPos.w"
			"|| centerNDCPos.y < -centerNDCPos.w"
			"|| centerNDCPos.y > centerNDCPos.w"
			"|| centerNDCPos.z < -centerNDCPos.w"
			"|| centerNDCPos.z > centerNDCPos.w)"
			"return;"*/

		// =====   Reference:

		// Upper
		//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags & 1;
		//if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z - 1).IsSolid() ) flags = flags & 2;
		//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags & 4;
		//if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z + 1).IsSolid() ) flags = flags & 8;

		// Middle
		//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags & 16;
		//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags & 32;
		//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags & 64;
		//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags & 128;

		// Lower
		//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y - 1, m_blockZ + z).IsSolid() ) flags = flags & 256;
		//if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z - 1).IsSolid() ) flags = flags & 512;
		//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY - y + 1, m_blockZ + z).IsSolid() ) flags = flags & 1024;
		//if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z + 1).IsSolid() ) flags = flags & 2048;

		"float u1 = float(vs_out[0].flags & 1) * 1;"
		"float u2 = float(vs_out[0].flags & 2) * 0.5;"
		"float u3 = float(vs_out[0].flags & 4) * 0.25;"
		"float u4 = float(vs_out[0].flags & 8) * 0.125;"

		"float m5 = float(vs_out[0].flags & 16) * 0.0625;"
		"float m6 = float(vs_out[0].flags & 32) * 0.03125;"
		"float m7 = float(vs_out[0].flags & 64) * 0.015625;"
		"float m8 = float(vs_out[0].flags & 128) * 0.0078125;"

		"float l9 = float(vs_out[0].flags & 256) * 0.00390625;"
		// Truncation problems start here...
		"float l10 = float(vs_out[0].flags & 512) * 0.001953125;"
		"float l11 = float(vs_out[0].flags & 1024) * 0.0009765625;"
		"float l12 = float(vs_out[0].flags & 2048) * 0.00048828125;"

		// -X
		"{"
			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * m5;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * m6;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m5 - shadowVal * l9;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m6 - shadowVal * l9;"
			"gs_out.normal = vec3(1, 0, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// +X
		"{"
			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * m7;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * m8;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m7 - shadowVal * l11;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"
			
			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m8 - shadowVal * l11;"
			"gs_out.normal = vec3(-1, 0, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// -Y
		/*"{"
			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color;"
			"gs_out.normal = vec3(0, 1, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"*/
		// +Y
		"{"
			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * u3;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * u2;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * u4;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * u4;"
			"gs_out.normal = vec3(0, -1, 0);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// -Z
		"{"
			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m6 - shadowVal * l10;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * m6;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m7 - shadowVal * l10;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * m7;"
			"gs_out.normal = vec3(0, 0, 1);"
			"EmitVertex();"
		"}"
		"EndPrimitive();"
		// +Z
		"{"
			"gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m8 - shadowVal * l12;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u4 - shadowVal * m8;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * m5 - shadowVal * l12;"
			"gs_out.normal = vec3(0, 0, -1);"
			"EmitVertex();"

			"gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));"
			"gs_out.color = vs_out[0].color - shadowVal * u4 - shadowVal * m5;"
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

	"uniform vec3 LightDir;"
	
	"void main()"
	"{"
		"vec3 l = normalize( LightDir );"
		"float cosTheta = clamp( dot(gs_out.normal, l), 0, 1 );"

		"color.xyz = "
			"gs_out.color * 0.6 +"
			"gs_out.color * cosTheta * 0.3;"
		"color.w = 1;"
	"}";

VCTerrianShader::VCTerrianShader():
	m_unifMVP(0),
	m_unifLightDir(0)
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
	// MVP
	glm::mat4 MVP = Shader::BoundCamera->ProjectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(m_unifMVP, 1, GL_FALSE, &MVP[0][0]);

	// Light Dir
	glm::vec4 lightInvDirWorld(VCShadowShader::LightInverseDirection.x, VCShadowShader::LightInverseDirection.y, VCShadowShader::LightInverseDirection.z, 1);
	glm::vec4 lightDirCameraSpace = Shader::BoundCamera->ViewMatrix * lightInvDirWorld;

	//"LightDirection_cameraspace = ( ViewMatrix * vec4( LightInvDirection_worldspace, 0 ) ).xyz;"

	glUniform3f(m_unifLightDir, lightDirCameraSpace.x, lightDirCameraSpace.y, lightDirCameraSpace.z);
	glErrorCheck();
}

void VCTerrianShader::BindAttribLocations()
{
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "position");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "color");
	glBindAttribLocation(m_programId, VC_ATTRIBUTE_FLAGS, "flags");

	glErrorCheck();
}

void VCTerrianShader::GetUniformIDs()
{
	// Vertex
	m_unifMVP = glGetUniformLocation(m_programId, "MVP");
	m_unifLightDir = glGetUniformLocation(m_programId, "LightDir");
	glErrorCheck();
}

void VCTerrianShader::PostInitialize()
{
}
