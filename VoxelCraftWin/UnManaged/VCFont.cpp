//
//  VCFont.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCFont.h"

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

	f.close();
	cout << "Done." << endl;
	cin.clear();
	cin.ignore();
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

	for ( int i = 0; i < m_common.pages; i++ )
	{
		string builder;
		while(true)
		{
			char inC = ReadInt8(f);

			if ( inC == 0 )
				break;

			builder.push_back(inC);
		}

		m_files.push_back(builder);
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