//
//  VCLexicalEngine.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCLexicalEngine.h"
#include "VCFont.h"
#include "VCMonoRuntime.h"
#include "VCGui.h"

VCLexicalEngine* VCLexicalEngine::Instance;

VCTextMetrics::VCTextMetrics()
{

}

VCTextMetrics::VCTextMetrics( int width, int height ) : TotalWidth(width), TotalHeight(height)
{

}

VCTextMetrics::~VCTextMetrics()
{

}

VCLexicalEngine::VCLexicalEngine(void) :
	m_fontsCount(0)
{
	VCLexicalEngine::Instance = this;
}

VCLexicalEngine::~VCLexicalEngine(void)
{
}

void VCLexicalEngine::Initialize()
{
}

std::string VCLexicalEngine::LoadFont ( std::string fntPath, std::string ddsPath, int* font )
{
	VCFont* vcfont = new VCFont(fntPath, ddsPath, m_fontsCount);
	vcfont->Initialize();

	for (int i = 0; i < m_fontsCount; i++ )
	{
		if (m_fonts[i]->Name == vcfont->Name)
		{
			VC_ERROR("Cannot load duplicate font: " << vcfont->Name);
		}
	}

	*font = m_fontsCount;
	m_fonts[m_fontsCount++] = vcfont;
	return vcfont->Name;
}

VCTextMetrics VCLexicalEngine::GetMetrics( int font, std::string text )
{
	VCFont* vcfont = m_fonts[font];
	int xOffset = 0;

	for ( int i = 0; i < text.length(); i++ )
	{
		char c = text[i];
		CharDesc cDesc = vcfont->Charaters[c];
		int kerning = i == 0 ? 0 : cDesc.KerningPairs[ text[i - 1] ];

		// Advance xOffset by xAdvance + kerning
		xOffset += cDesc.XAdvance + kerning;
	}

	return VCTextMetrics(xOffset, vcfont->Common.lineHeight);
}

int VCLexicalEngine::MakeTextToQuadBuffer( int font, std::string text, VCPoint llPoint, GLubyte4 color, GlyphVerticie* buffer, int offset, float depthStep )
{
	VCFont* vcfont = m_fonts[font];
	int xOffset = 0;
	llPoint.Y += vcfont->Common.lineHeight;

	for ( int i = 0; i < text.length(); i++ )
	{
		char c = text[i];
		CharDesc cDesc = vcfont->Charaters[c];
		int kerning = i == 0 ? 0 : cDesc.KerningPairs[ text[i - 1] ];

		// Advance verts by xOffset + kerning, set color, add to vector
		for ( int v = 0; v < 6; v++ )
		{
			cDesc.Quad[v].Position.x += xOffset + kerning + llPoint.X;
			cDesc.Quad[v].Position.y += llPoint.Y;
			cDesc.Quad[v].Position.z = VCGui::Instance->DepthStep++; //depthStep;
			cDesc.Quad[v].Color = color;

			// Optimized to a memcpy ( 30% frame time -> 8% frame time )
			//buffer[(i * 6) + v + offset] = cDesc.Quad[v];
		}

		memcpy(&buffer[(i * 6) + offset], cDesc.Quad, sizeof(GlyphVerticie) * 6);

		// Advance xOffset by xAdvance + kerning
		xOffset += cDesc.XAdvance + kerning;
	}

	return text.length() * 6;
}

VCFont* VCLexicalEngine::GetFontById( int fontID )
{
	if (fontID >= m_fontsCount)
	{
		VC_ERROR("Font ID: " << fontID << " not loaded into VCLexEngine.");
	}

	return m_fonts[fontID];
}

// ================================      Interop      ============
void VCLexicalEngine::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("Font::VCInteropLoadFont",	(void*)VCInteropLoadFont);
}

VCMonoStringPtr VCInteropLoadFont (VCMonoStringPtr fntPath, VCMonoStringPtr ddsPath, int* fontOut)
{
	std::string name = VCLexicalEngine::Instance->LoadFont(VCMonoString(fntPath), VCMonoString(ddsPath), fontOut);
	return VCMonoString::MakeString(name.c_str());
}
