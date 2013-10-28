//
//  VCStreamHelpers.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCStreamHelpers.h"

char ReadInt8( std::ifstream& f )
{
	char value;
	f.read((char*)&value, 1);
	return value;
}

short ReadInt16( std::ifstream& f )
{
	short value;
	//f >> value;
	f.read((char*) &value, 2);

	return value;
}

int ReadInt32( std::ifstream& f )
{
	int value;
	//f >> value;
	f.read((char*) &value, 4);

	return value;
}

void WriteInt8( std::ofstream& f, char value )
{
	f.write((char*) &value, 1);
}

void WriteInt16( std::ofstream& f, short value )
{
	f.write((char*) &value, 2);
}

void WriteInt32( std::ofstream& f, int value )
{
	f.write((char*) &value, 4);
}
