//
//  VCTypes.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "PCH.h"

struct GLubyte3
{
	GLubyte3() {};

	GLubyte3(GLubyte x, GLubyte y, GLubyte z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	GLubyte x;
	GLubyte y;
	GLubyte z;
};

struct GLbyte3
{
	GLbyte3() {};

	GLbyte3(GLbyte x, GLbyte y, GLbyte z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	GLbyte x;
	GLbyte y;
	GLbyte z;
};

struct GLubyte4
{
	GLubyte4() {};

	GLubyte4(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	GLubyte x;
	GLubyte y;
	GLubyte z;
	GLubyte w;
};

struct GLbyte4
{
	GLbyte4() {};

	GLbyte4(GLbyte x, GLbyte y, GLbyte z, GLbyte w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	GLbyte x;
	GLbyte y;
	GLbyte z;
	GLbyte w;
};

struct GLshort3
{
	GLshort3() {};

	GLshort3(GLshort x, GLshort y, GLshort z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	GLshort x;
	GLshort y;
	GLshort z;
};

struct GLushort2
{
	GLushort2() {};

	GLushort2(GLushort x, GLushort y )
	{
		this->x = x;
		this->y = y;
	}

	GLushort x;
	GLushort y;
};

struct GLushort3
{
	GLushort3() {};

	GLushort3(GLushort x, GLushort y, GLushort z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	GLushort x;
	GLushort y;
	GLushort z;
};

struct GLfloat2
{
	GLfloat2() {};

	GLfloat2(GLfloat x, GLfloat y )
	{
		this->x = x;
		this->y = y;
	}

	GLfloat x;
	GLfloat y;
};

struct GLfloat3
{
	GLfloat3() {};

	GLfloat3(GLfloat x, GLfloat y, GLfloat z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct GLfloat4
{
	GLfloat4() {};

	GLfloat4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

struct Point
{
	Point() {};
	Point(int x, int y) : X(x), Y(y) {}
	int X;
	int Y;

};

struct Rectangle
{
    Rectangle() {};
    Rectangle(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}
    int X;
    int Y;
    int Width;
    int Height;
    
};

struct vcint2
{
	vcint2(): X(0), Y(0) {};
	vcint2(int x, int y, int z): X(x), Y(y) {}
	int X;
	int Y;
};

struct vcint3
{
	vcint3(): X(0), Y(0), Z(0) {};
	vcint3(int x, int y, int z): X(x), Y(y), Z(z) {}
	int X;
	int Y;
	int Z;
};

struct vcint4
{
	vcint4(): X(0), Y(0), Z(0), W(0) {};
	vcint4(int x, int y, int z, int w): X(x), Y(y), Z(z), W(w) {}
	int X;
	int Y;
	int Z;
	int W;
};
