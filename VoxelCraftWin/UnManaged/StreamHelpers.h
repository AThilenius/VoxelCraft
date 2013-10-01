//
//  StreamHelpers.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <intrin.h>

using namespace std;


inline char ReadInt8 ( ifstream& f )
{
	char value;
	f.read((char*)&value, 1);
	return value;
}

inline short ReadInt16 ( ifstream& f )
{
	short value;
	//f >> value;
	f.read((char*) &value, 2);

	return value;
}

inline int ReadInt32 ( ifstream& f )
{
	int value;
	//f >> value;
	f.read((char*) &value, 4);

	return value;
}