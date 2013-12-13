//
//  VCTextBuilder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTextBuilder.h"
#include "VCTextBuffer.h"
#include "VCLexicalEngine.h"

VCTextBuilder::VCTextBuilder( void )
{

}

VCTextBuilder::~VCTextBuilder( void )
{

}

void VCTextBuilder::Initialize()
{
}

void VCTextBuilder::Reset()
{
}

void VCTextBuilder::DrawText( int font, std::string text, VCPoint llPoint, GLubyte4 color, float depthStep )
{
	for (int i = m_bufferByFont.size(); m_bufferByFont.size() <= font; i++)
	{
		VCTextBuffer* vcTextBuffer = new VCTextBuffer(VCLexicalEngine::Instance->GetFontById(i));
		vcTextBuffer->Initialize();
		m_bufferByFont.push_back( vcTextBuffer );
	}

	m_bufferByFont[font]->DrawText(text, llPoint, color, depthStep);
}
