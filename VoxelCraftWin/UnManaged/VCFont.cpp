//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCShader.h"

#include "VCFont.h"
#include "VCGLRenderer.h"
#include "VCStreamHelpers.h"
#include "VCTexture.h"
#include "VCResourceManager.h"


GlyphVerticie::GlyphVerticie()
{

}

GlyphVerticie::GlyphVerticie( GLshort3 poistion, GLfloat2 uvDXFormat, GLubyte4 color ) :
	Position(poistion),
	UV(uvDXFormat),
	Color(color)
{

}

CharDesc::CharDesc()
{
	memset(KerningPairs, 0, sizeof(KerningPairs));
}

VCFont::VCFont(std::string fntPath, std::string ddsPath, int id) :
	m_fntPath(fntPath),
	m_ddsPath(ddsPath),
	FontID(id)
{
}


VCFont::~VCFont(void)
{
}


void VCFont::Initialize()
{
	std::ifstream f (m_fntPath, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cout << "Failed to open file: " << m_fntPath << std::endl;
		return;
	}

	// Header
	char c1, c2, c3, c4;
	f >> c1 >> c2 >> c3 >> c4;
	if (c1 != 66 || c2 != 77 || c3 != 70 || c4 != 3)
	{
		std::cout << "FNT must be binary, version 3!" << std::endl;
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
	//m_ddsTexture = VCTexture::CreateUnfilteredTexture(m_ddsPath.c_str());
	VCTextureParams tparam;
	tparam.Filtering = VCTextureFiltering::None;
	m_ddsTexture = VCResourceManager::GetTexure(m_ddsPath, tparam);

	// Name
	std::ostringstream ss;
	ss << FontName << "-" << Info.fontSize;

	if ( Info.bitField & 32)
		ss << "-Italic";

	if ( Info.bitField & 16)
		ss << "-Bold";

	Name = ss.str();
}


bool VCFont::ParseInfo(std::ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	f.read((char*) &Info, sizeof(InfoHeader));

	while(true)
	{
		char inC = ReadInt8(f);

		if ( inC == 0 )
			break;

		FontName.push_back(inC);
	}

	Size = Info.fontSize;

	return true;
}

bool VCFont::ParseCommon(std::ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	f.read((char*) &Common, 15);
	
	return true;
}

bool VCFont::ParsePages(std::ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	if ( Common.pages != 1 )
	{
		VC_ERROR("Only 1 font page per font is supported.");
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

bool VCFont::ParseCharacters(std::ifstream& f)
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

bool VCFont::ParseKerning(std::ifstream& f)
{
	char blockType = ReadInt8(f);
	int blockSize = ReadInt32(f);

	int kerningCount = blockSize / 10;

	// Pre-Buffer data ( Used to be a bottleneck - Profiled )
	KerningPairIMR* pairsIMR = (KerningPairIMR*) malloc (sizeof(KerningPairIMR) * kerningCount);
	int size = sizeof(KerningPairIMR);
	//f.read((char*)pairsIMR, sizeof(KerningPairIMR) * kerningCount);

	for ( int i = 0; i < kerningCount; i++ )
	{
		// Truncated Endian swap ( Truncated to 8 bits, hopefully enough )
		//KerningPairIMR p = pairsIMR[i];
		//p.first = p.first >> 28;
		//p.second = p.second >> 28;
		//p.ammount = p.ammount >> 8;
		//
		//Charaters[p.second].KerningPairs[p.first] = p.ammount;
		unsigned int first = ReadInt32(f);
		unsigned int second = ReadInt32(f);
		short ammount = ReadInt16(f);
		//Int8 sh = 0;

		Charaters[second].KerningPairs[first] = ammount;

	}

	free(pairsIMR);

	return true;
}

void VCFont::PreCompileQuads()
{
	float width = Common.scaleW;
	float height = Common.scaleH;

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
