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

class VCLexicalEngine
{
public:
	VCLexicalEngine(void);
	~VCLexicalEngine(void);

	void Initialize();
	void LoadFont ( string name, string fntPath, string ddsPath );

	GLuint MakeTextVAO ( string font, string text, int left, int down, GLubyte4 color );

	static VCLexicalEngine* Instance;

private:
	typedef unordered_map<string, VCFont*> FontsMap;
	FontsMap m_fonts;

};

