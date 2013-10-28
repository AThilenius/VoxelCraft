//
//  VCGeometryTypes.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct Point
{
	Point();
	Point(int x, int y);
	int X;
	int Y;

};

struct Rectangle
{
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	int X;
	int Y;
	int Width;
	int Height;

};

struct RectangleF
{
	RectangleF();
	RectangleF(float x, float y, float width, float height);
	float X;
	float Y;
	float Width;
	float Height;

};