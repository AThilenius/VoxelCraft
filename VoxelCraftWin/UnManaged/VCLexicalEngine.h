//
//  VCLexicalEngine.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCFont.h"
#include "VCRenderState.h"
#include "VCText.h"

class VCLexicalEngine
{
public:
	VCLexicalEngine(void);
	~VCLexicalEngine(void);

	void Initialize();
	void LoadFont ( string name, string fntPath, string ddsPath );

	VCText* MakeText ( string font, string text, int left, int down, GLubyte4 color );
	VCRenderState* GetRStateForFont ( string font )
	{
		auto iter = m_fonts.find(font);

		if ( iter == m_fonts.end() )
		{
			ERROR("Font: " << font << " not added to Lexical Engine");
		}

		VCFont* vcfont = (*iter).second;
		return vcfont->RenderState;
	}

	static VCLexicalEngine* Instance;

private:
	typedef unordered_map<string, VCFont*> FontsMap;
	FontsMap m_fonts;

};

