//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include <string>

struct GlyphVerticie
{
	GlyphVerticie();
	GlyphVerticie(GLshort3 poistion, GLfloat2 uvDXFormat, GLubyte4 color);

	GLshort3 Position;
	GLfloat2 UV;
	GLubyte4 Color;
};

struct CharDesc
{
	CharDesc();

	unsigned short X;
	unsigned short Y;
	unsigned short Width;
	unsigned short Height;
	short XOffset;
	short YOffset;
	short XAdvance;
	unsigned char Page;
	unsigned char Chanel;

	GlyphVerticie Quad[6];
	char KerningPairs[256];
};

struct InfoHeader
{
	short fontSize;
	char bitField;
	unsigned char charSet;
	unsigned short stretchH;	
	unsigned char aa;
	unsigned char paddingUp;
	unsigned char paddingRight;
	unsigned char paddingDown;
	unsigned char paddingLeft;
	unsigned char spacingHoriz;
	unsigned char spacingVert;
	unsigned char outline;
};

struct CommonHeader
{
	unsigned short lineHeight;
	unsigned short base;
	unsigned short scaleW;
	unsigned short scaleH;
	unsigned short pages;
	unsigned char commonBitField;
	unsigned char alphaChnl;
	unsigned char redChnl;
	unsigned char greenChnl;
	unsigned char blueChnl;
};

struct KerningPairIMR
{
	unsigned int first;
	unsigned int second;
	short ammount;
};

class VCFont
{
public:
	VCFont(std::string fntPath, VCGLTexture* texture, int id);
	~VCFont(void);

	void Initialize();

	std::string Name;
	int FontID;
	int Size;

private:
	bool ParseInfo(std::ifstream& f);
	bool ParseCommon(std::ifstream& f);
	bool ParsePages(std::ifstream& f);
	bool ParseCharacters(std::ifstream& f);
	bool ParseKerning(std::ifstream& f);
	void PreCompileQuads();

	std::string m_imageFileName;
	VCGLTexture* m_ddsTexture;

	CharDesc Charaters[256];
	std::string m_fntPath;

	// Info:
	InfoHeader Info;
	CommonHeader Common;
	std::string FontName;

	friend class VCLexicalEngine;
	friend class VCTextBuffer;
};

