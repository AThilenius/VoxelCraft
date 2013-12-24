////
////  VCMeshSection.h
////  VoxelCraft
////
////  Created by Alec Thilenius on 12/23/2013.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCMeshSection.h"
//#include "VCShader.h"
//
//VCMeshSection::VCMeshSection()
//{
//
//}
//
//VCMeshSection::~VCMeshSection()
//{
//
//}
//
//void VCMeshSection::Initialize( VCPuvnVerticie* verts, UInt32* indicies, int vCount, int iCount )
//{
//	VertexCount = vCount;
//	IndexCount = iCount;
//
//	// Create VAO
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//	glErrorCheck();
//
//	// Create Verticie VBO
//	glGenBuffers(1, &m_vertextVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vertextVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(VCPuvnVerticie) * VertexCount, verts, GL_STATIC_DRAW);
//	ZERO_CHECK(m_vertextVBO);
//
//	// Create Index VBO
//	glGenBuffers(1, &m_indexVBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UInt32) * iCount, indicies, GL_STATIC_DRAW);
//	ZERO_CHECK(m_vertextVBO);
//
//	// Bind Attributes
//	glEnableVertexAttribArray(VCShaderAttribute::Position0);
//	glEnableVertexAttribArray(VCShaderAttribute::TexCoord0);
//	glEnableVertexAttribArray(VCShaderAttribute::Normal0);
//
//	glVertexAttribPointer(VCShaderAttribute::Position0,	3,	GL_FLOAT,	GL_FALSE,	sizeof(VCPuvnVerticie),	(void*) offsetof(VCPuvnVerticie, Position) );
//	glVertexAttribPointer(VCShaderAttribute::TexCoord0,	2,	GL_FLOAT,	GL_FALSE,	sizeof(VCPuvnVerticie),	(void*) offsetof(VCPuvnVerticie, UV) );
//	glVertexAttribPointer(VCShaderAttribute::Normal0,	3,	GL_FLOAT,	GL_FALSE,	sizeof(VCPuvnVerticie),	(void*) offsetof(VCPuvnVerticie, Normal) );
//
//	glBindVertexArray(0);
//}
//
//void VCMeshSection::Render()
//{
//
//}
