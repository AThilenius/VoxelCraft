////
////  VCTerrainConstructionShader.cpp
////  VoxelCraftOSX
////
////  Created by Alec Thilenius on 11/21/13.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCTerrainConstructionShader.h"
//
//#include "VCCamera.h"
//#include "VCShadowShader.h"
//#include "VCCamera.h"
//
//
//VCTerrainConstructionShader::VCTerrainConstructionShader()
//{
//	m_vertexShader = "TerrainConstruction";
//	m_geometryShader = "TerrainConstruction";
//}
//
//VCTerrainConstructionShader::~VCTerrainConstructionShader(void)
//{
//}
//
//void VCTerrainConstructionShader::BindAttribLocations()
//{
//	glBindAttribLocation(m_programId, VC_ATTRIBUTE_POSITION, "positionIn");
//	glBindAttribLocation(m_programId, VC_ATTRIBUTE_COLOR, "colorIn");
//	glBindAttribLocation(m_programId, VC_ATTRIBUTE_FLAGS, "flagsIn");
//	
//	glErrorCheck();
//}
//
//void VCTerrainConstructionShader::PreLink()
//{
//	// Specify the GS outputs
//
//	const GLchar* Varyings[1]; 
//	Varyings[0] = "gl_Position";
//	//Varyings[1] = "normalOut";
//	//Varyings[2] = "colorOut";
//	
//	glTransformFeedbackVaryings(m_programId, 1, Varyings, GL_INTERLEAVED_ATTRIBS); 
//}
//
//void VCTerrainConstructionShader::GetUniformIDs()
//{
//}
//
//void VCTerrainConstructionShader::PostInitialize()
//{
//}
