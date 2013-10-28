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
#include "VCText.h"
#include "VCMonoRuntime.h"

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

VCLexicalEngine::VCLexicalEngine(void)
{
	VCLexicalEngine::Instance = this;
}

VCLexicalEngine::~VCLexicalEngine(void)
{
}

void VCLexicalEngine::Initialize()
{
}

std::string VCLexicalEngine::LoadFont ( std::string fntPath, std::string ddsPath )
{
	VCFont* font = new VCFont(fntPath, ddsPath);
	font->Initialize();

	m_fonts.insert(FontsMap::value_type(font->Name, font));
	return font->Name;
}

VCText* VCLexicalEngine::MakeText ( std::string font, std::string text, int left, int down, GLubyte4 color )
{
	auto iter = m_fonts.find(font);
	
	if ( iter == m_fonts.end() )
	{
		VC_ERROR("Font: " << font << " not added to Lexical Engine");
	}

	VCFont* vcfont = (*iter).second;

	GlyphVerticie* verts = (GlyphVerticie*) malloc(sizeof(GlyphVerticie) * text.length() * 6);
	int xOffset = 0;

	for ( int i = 0; i < text.length(); i++ )
	{
		char c = text[i];
		CharDesc cDesc = vcfont->Charaters[c];
		int kerning = i == 0 ? 0 : cDesc.KerningPairs[ text[i - 1] ];

		// Advance verts by xOffset + kerning, set color, add to vector
		for ( int v = 0; v < 6; v++ )
		{
			cDesc.Quad[v].Position.x += xOffset + kerning + left;
			cDesc.Quad[v].Position.y += down;
			cDesc.Quad[v].Color = color;
			verts[i * 6 + v] = cDesc.Quad[v];
		}

		// Advance xOffset by xAdvance + kerning
		xOffset += cDesc.XAdvance + kerning;
	}

	GLuint vaoId;
	GLuint vboId;

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// Data
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GlyphVerticie) * text.length() * 6, &verts[0], GL_STATIC_DRAW);

	// Verts
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glVertexAttribPointer( VC_ATTRIBUTE_POSITION,		3,	GL_SHORT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Position));

	glEnableVertexAttribArray(VC_ATTRIBUTE_TEX_COORD_0);
	glVertexAttribPointer( VC_ATTRIBUTE_TEX_COORD_0,	2,	GL_FLOAT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, UV));

	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
	glVertexAttribPointer( VC_ATTRIBUTE_COLOR,			4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Color));

	glBindVertexArray(0);
	free(verts);

	return new VCText(vcfont->RenderState, vaoId, vboId, text.length() * 6, xOffset, vcfont->Size);
}

VCTextMetrics VCLexicalEngine::GetMetrics( std::string font, std::string text )
{
	auto iter = m_fonts.find(font);

	if ( iter == m_fonts.end() )
	{
		VC_ERROR("Font: " << font << " not added to Lexical Engine");
	}

	VCFont* vcfont = (*iter).second;
	int xOffset = 0;

	for ( int i = 0; i < text.length(); i++ )
	{
		char c = text[i];
		CharDesc cDesc = vcfont->Charaters[c];
		int kerning = i == 0 ? 0 : cDesc.KerningPairs[ text[i - 1] ];

		// Advance xOffset by xAdvance + kerning
		xOffset += cDesc.XAdvance + kerning;
	}

	return VCTextMetrics(xOffset, vcfont->Size);
}

int VCLexicalEngine::MakeTextToQuadBuffer( std::string font, std::string text, int left, int down, GLubyte4 color, GlyphVerticie* buffer, int offset )
{
	auto iter = m_fonts.find(font);

	if ( iter == m_fonts.end() )
	{
		VC_ERROR("Font: " << font << " not added to Lexical Engine");
	}

	VCFont* vcfont = (*iter).second;

	int xOffset = 0;

	for ( int i = 0; i < text.length(); i++ )
	{
		char c = text[i];
		CharDesc cDesc = vcfont->Charaters[c];
		int kerning = i == 0 ? 0 : cDesc.KerningPairs[ text[i - 1] ];

		// Advance verts by xOffset + kerning, set color, add to vector
		for ( int v = 0; v < 6; v++ )
		{
			cDesc.Quad[v].Position.x += xOffset + kerning + left;
			cDesc.Quad[v].Position.y += down;
			cDesc.Quad[v].Color = color;
			buffer[(i * 6) + v + offset] = cDesc.Quad[v];
		}

		// Advance xOffset by xAdvance + kerning
		xOffset += cDesc.XAdvance + kerning;
	}

	return text.length() * 6;
}

VCRenderState* VCLexicalEngine::GetRStateForFont( std::string font )
{
	auto iter = m_fonts.find(font);

	if ( iter == m_fonts.end() )
	{
		VC_ERROR("Font: " << font << " not added to Lexical Engine");
	}

	VCFont* vcfont = (*iter).second;
	return vcfont->RenderState;
}

// ================================      Interop      ============
void VCLexicalEngine::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("Gui::VCInteropLoadFont",	(void*)VCInteropLoadFont);
}

VCMonoStringPtr VCInteropLoadFont (VCMonoStringPtr fntPath, VCMonoStringPtr ddsPath)
{
	std::string name = VCLexicalEngine::Instance->LoadFont(VCMonoString(fntPath), VCMonoString(ddsPath));
	return VCMonoString::MakeString(name.c_str());
}
