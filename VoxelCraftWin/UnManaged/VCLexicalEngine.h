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
	std::string LoadFont ( std::string fntPath, std::string ddsPath, int* fontOut );

	VCTextMetrics GetMetrics ( int font, std::string text ); 
	int MakeTextToQuadBuffer ( int font, std::string text, VCPoint llPoint, GLubyte4 color, GlyphVerticie* buffer, int offset, float depthStep);
	VCFont* GetFontById ( int fontID );

	static VCLexicalEngine* Instance;

private:
	VCFont* m_fonts[50];
	int m_fontsCount;
};

// Interop
DLL_EXPORT_API void VCInteropLoadFont (char* fntPath, char* ddsPath, int* fontOut);

