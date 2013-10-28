//
//  VCLexicalEngine.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCText;
class VCRenderState;
class VCFont;
struct GlyphVerticie;

#include <unordered_map>
#include "VCAllPrimitives.h"

struct VCTextMetrics
{
	int TotalWidth;
	int TotalHeight;

	VCTextMetrics();
	VCTextMetrics(int width, int height);
	~VCTextMetrics();
};

class VCLexicalEngine
{
public:
	VCLexicalEngine(void);
	~VCLexicalEngine(void);

	void Initialize();
	std::string LoadFont ( std::string fntPath, std::string ddsPath );

	VCText* MakeText ( std::string font, std::string text, int left, int down, GLubyte4 color );
	VCTextMetrics GetMetrics ( std::string font, std::string text ); 
	int MakeTextToQuadBuffer ( std::string font, std::string text, int left, int down, GLubyte4 color, GlyphVerticie* buffer, int offset);
	VCRenderState* GetRStateForFont ( std::string font );

	static VCLexicalEngine* Instance;

private:
	typedef std::unordered_map<std::string, VCFont*> FontsMap;
	FontsMap m_fonts;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
MonoString* VCInteropLoadFont (MonoString* fntPath, MonoString* ddsPath);

