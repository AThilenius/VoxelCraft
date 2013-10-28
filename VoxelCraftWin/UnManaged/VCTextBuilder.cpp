//
//  VCTextBuilder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTextBuilder.h"

#include "VCLexicalEngine.h"
#include "VCText.h"

VCTextBuilder::VCTextBuilder( void )
{

}

VCTextBuilder::~VCTextBuilder( void )
{

}

void VCTextBuilder::Reset()
{
	for (int i = 0; i < m_text.size(); i++)
		delete m_text[i];

	m_text.clear();
}

void VCTextBuilder::Initialize()
{

}

void VCTextBuilder::DrawText( std::string text, Point llPoint, std::string font /*= "Cambria-16"*/, GLubyte4 color /*= GLubyte4(255, 255, 255, 255) */ )
{
	VCText* vctext = VCLexicalEngine::Instance->MakeText(font, text, llPoint.X, llPoint.Y, color);
	m_text.push_back(vctext);
}
