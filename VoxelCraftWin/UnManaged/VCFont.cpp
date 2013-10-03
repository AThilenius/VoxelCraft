//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCFont.h"
#include "VCGLRenderer.h"
#include "StreamHelpers.h"

VCFont::VCFont(string fntPath, string ddsPath) :
	m_fntPath(fntPath),
	m_ddsPath(ddsPath)
{
}


VCFont::~VCFont(void)
{
}


void VCFont::Initialize()
{
	ifstream f (m_fntPath, ios::in | ios::binary);
	if (!f.is_open())
	{
		cout << "Failed to open file: " << m_fntPath << endl;
		return;
	}

	// Header
	char c1, c2, c3, c4;
	f >> c1 >> c2 >> c3 >> c4;
	if (c1 != 66 || c2 != 77 || c3 != 70 || c4 != 3)
	{
		cout << "FNT must be binary, version 3!" << endl;
		return;
	}
	
	if (!ParseInfo(f))
		return;

	if (!ParseCommon(f) )
		return;

	if (!ParsePages(f) )
		return;

	if (!ParseCharacters(f) )
		return;

	if (!ParseKerning(f) )
		return;

	PreCompileQuads();

	f.close();

	// Load DDS
	m_ddsTexture = loadDDS ( m_ddsPath.c_str() );

	// Name
	ostringstream ss;
	ss << m_fontName << "-" << m_info.fontSize;

	if ( m_info.bitField & 32)
		ss << "-Italic";

	if ( m_info.bitField & 16)
		ss << "-Bold";

	Name = ss.str();

	// Create a render state for text rendering
	RenderState = new VCRenderState();
	RenderState->StageCount = 1;
	RenderState->BatchingOrder = VC_BATCH_GUI;
	RenderState->Stages[0].Shader = VCGLRenderer::Instance->LexShader;
	RenderState->Stages[0].Textures[0] = m_ddsTexture;
	RenderState->Stages[0].DepthTest = false;
	VCGLRenderer::Instance->RegisterState(RenderState);
}


bool VCFont::ParseInfo(ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	f.read((char*) &m_info, sizeof(InfoHeader));

	while(true)
	{
		char inC = ReadInt8(f);

		if ( inC == 0 )
			break;

		m_fontName.push_back(inC);
	}

	return true;
}

bool VCFont::ParseCommon(ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	f.read((char*) &m_common, 15);
	
	return true;
}

bool VCFont::ParsePages(ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	if ( m_common.pages != 1 )
	{
		ERROR("Only 1 font page per font is supported.");
	}

	while(true)
	{
		char inC = ReadInt8(f);

		if ( inC == 0 )
			break;

		m_imageFileName.push_back(inC);
	}
	
	return true;
}

bool VCFont::ParseCharacters(ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	int charCount = blockSize / 20;

	for ( int i = 0; i < charCount; i++ )
	{
		unsigned int id = ReadInt32(f);
		f.read((char*) &Charaters[id], 16);
	}

	return true;
}

bool VCFont::ParseKerning(ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	int kerningCount = blockSize / 10;

	for ( int i = 0; i < kerningCount; i++ )
	{
		unsigned int first = ReadInt32(f);
		unsigned int second = ReadInt32(f);
		short ammount = ReadInt16(f);

		Charaters[second].KerningPairs[first] = ammount;
	}

	return true;
}

void VCFont::PreCompileQuads()
{
	float width = m_common.scaleW;
	float height = m_common.scaleH;

	GLubyte4 color ( 255, 255, 255, 255 );

	for ( int i = 0; i < 256; i++ )
	{
		
		// Lower Left
		GLshort3 llp ( 
			Charaters[i].XOffset, 
			-Charaters[i].YOffset - Charaters[i].Height, 
			0 );

		GLfloat2 llUV (
			Charaters[i].X / width,
			(Charaters[i].Y + Charaters[i].Height) / height);


		// Upper Left
		GLshort3 ulp ( 
			Charaters[i].XOffset, 
			-Charaters[i].YOffset, 
			0 );

		GLfloat2 ulUV (
			Charaters[i].X / width,
			Charaters[i].Y / height);
		

		// Lower Right
		GLshort3 lrp ( 
			Charaters[i].XOffset + Charaters[i].Width, 
			-Charaters[i].YOffset - Charaters[i].Height, 
			0 );

		GLfloat2 lrUV (
			(Charaters[i].X + Charaters[i].Width) / width,
			(Charaters[i].Y + Charaters[i].Height) / height);


		// Upper right
		GLshort3 urp ( 
			Charaters[i].XOffset + Charaters[i].Width, 
			-Charaters[i].YOffset, 
			0 );

		GLfloat2 urUV (
			(Charaters[i].X + Charaters[i].Width) / width,
			Charaters[i].Y / height);


		Charaters[i].Quad[0] = GlyphVerticie ( ulp, ulUV, color );
		Charaters[i].Quad[1] = GlyphVerticie ( llp, llUV, color );
		Charaters[i].Quad[2] = GlyphVerticie ( lrp, lrUV, color );
		
		Charaters[i].Quad[3] = GlyphVerticie ( ulp, ulUV, color );
		Charaters[i].Quad[4] = GlyphVerticie ( lrp, lrUV, color );
		Charaters[i].Quad[5] = GlyphVerticie ( urp, urUV, color );
	}
}