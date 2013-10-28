//
//  VCGeometryTypes.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCPoint
{
public:
	VCPoint();
	VCPoint(int x, int y);
	int X;
	int Y;

};

class VCRectangle
{
public:
	VCRectangle();
	VCRectangle(int x, int y, int width, int height);
	int X;
	int Y;
	int Width;
	int Height;

};

class VCRectangleF
{
public:
	VCRectangleF();
	VCRectangleF(float x, float y, float width, float height);
	float X;
	float Y;
	float Width;
	float Height;

};