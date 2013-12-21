////
////  VCLexShader.cpp
////  VoxelCraftOSX
////
////  Created by Alec Thilenius on 9/1/13.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCLexShader.h"
//
//#include "VCWindow.h"
//
//
//VCLexShader::VCLexShader(void):
//	m_unifProjMatrix(-1),
//	m_unifGlyphsTex(-1)
//{
//	m_vertexShader = "Lex";
//	m_fragShader = "Lex";
//}
//
//
//VCLexShader::~VCLexShader(void)
//{
//}
//
//void VCLexShader::Bind(VCCamera* camera)
//{
//	// Takes a null camera
//	VCShader::Bind(camera);
//
//	// Set Projection Matrix and Tex unit
//	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -100000, -1);
//	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
//}
//
//
//void VCLexShader::BindAttribLocations()
//{
//	glBindAttribLocation(m_programId, VCShaderAttribute::Position0, "Position");
//	glBindAttribLocation(m_programId, VCShaderAttribute::TexCoord0, "UV");
//	glBindAttribLocation(m_programId, VCShaderAttribute::Color0, "Color");
//
//	glErrorCheck();
//}
//
//void VCLexShader::GetUniformIDs()
//{
//	m_unifProjMatrix = glGetUniformLocation(m_programId, "projMatrix");
//	m_unifGlyphsTex = glGetUniformLocation(m_programId, "glyphs");
//
//	glErrorCheck();
//}
//
//void VCLexShader::PostInitialize()
//{
//	// Set Projection Matrix and Tex unit
//	glm::mat4 projectionMatrix = glm::ortho<float>(0, VCWindow::Instance->Width, 0, VCWindow::Instance->Height, -100000, -1);
//	glUniformMatrix4fv(m_unifProjMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
//
//	glUniform1i(m_unifGlyphsTex, 0);
//}