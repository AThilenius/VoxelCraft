//
//  VCXIntX.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct vcint2
{
	vcint2();
	vcint2(int x, int y);
	int X;
	int Y;
};

struct vcint3
{
	vcint3();
	vcint3(int x, int y, int z);
	int X;
	int Y;
	int Z;
};

struct vcint4
{
	vcint4();
	vcint4(int x, int y, int z, int w);
	int X;
	int Y;
	int Z;
	int W;
};