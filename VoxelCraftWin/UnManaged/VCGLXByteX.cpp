//
//  VCGLXByteX.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLXByteX.h"

GLubyte3::GLubyte3()
{

}

GLubyte3::GLubyte3( GLubyte x, GLubyte y, GLubyte z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

GLbyte3::GLbyte3()
{

}

GLbyte3::GLbyte3( GLbyte x, GLbyte y, GLbyte z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

GLubyte4::GLubyte4()
{

}

GLubyte4::GLubyte4( GLubyte x, GLubyte y, GLubyte z, GLubyte w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

bool operator==( const GLubyte4& lhs, const GLubyte4& rhs )
{
	return 
		lhs.x == rhs.x && 
		lhs.y == rhs.y &&
		lhs.z == rhs.z &&
		lhs.w == rhs.w;
}

GLbyte4::GLbyte4()
{

}

GLbyte4::GLbyte4( GLbyte x, GLbyte y, GLbyte z, GLbyte w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
