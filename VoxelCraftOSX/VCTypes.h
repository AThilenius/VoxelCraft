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