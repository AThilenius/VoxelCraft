//
//  VCLexicalEngine.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCLexicalEngine.h"

VCLexicalEngine* VCLexicalEngine::Instance;

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

string VCLexicalEngine::LoadFont ( string fntPath, string ddsPath )
{
	VCFont* font = new VCFont(fntPath, ddsPath);
	font->Initialize();

	m_fonts.insert(FontsMap::value_type(font->Name, font));
	return font->Name;
}

VCText* VCLexicalEngine::MakeText ( string font, string text, int left, int up, GLubyte4 color )
{
	auto iter = m_fonts.find(font);
	
	if ( iter == m_fonts.end() )
	{
		ERROR("Font: " << font << " not added to Lexical Engine");
	}

	VCFont* vcfont = (*iter).second;


	vector<GlyphVerticie> verts;
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
			cDesc.Quad[v].Position.y += up;
			cDesc.Quad[v].Color = color;
			verts.push_back(cDesc.Quad[v]);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GlyphVerticie) * verts.size(), &verts[0], GL_STATIC_DRAW);

	// Verts
	glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
	glVertexAttribPointer( VC_ATTRIBUTE_POSITION,		3,	GL_SHORT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Position));

	glEnableVertexAttribArray(VC_ATTRIBUTE_TEX_COORD_0);
	glVertexAttribPointer( VC_ATTRIBUTE_TEX_COORD_0,	2,	GL_FLOAT,			GL_FALSE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, UV));

	glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);
	glVertexAttribPointer( VC_ATTRIBUTE_COLOR,			4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GlyphVerticie),	(void*) offsetof(GlyphVerticie, Color));

	glBindVertexArray(0);

	return new VCText(vcfont->RenderState, vaoId, vboId, verts.size());
}

// ================================      Interop      ============
void VCLexicalEngine::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Gui::VCInteropLoadFont",	(void*)VCInteropLoadFont);
}

MonoString* VCInteropLoadFont (MonoString* fntPath, MonoString* ddsPath)
{
	string name = VCLexicalEngine::Instance->LoadFont(mono_string_to_utf8(fntPath), mono_string_to_utf8(ddsPath));
	return mono_string_new(mono_domain_get(), name.c_str());
}