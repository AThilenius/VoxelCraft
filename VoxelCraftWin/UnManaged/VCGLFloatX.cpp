//
//  VCGLFloatX.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLFloatX.h"


GLfloat2::GLfloat2()
{

}

GLfloat2::GLfloat2( GLfloat x, GLfloat y )
{
	this->x = x;
	this->y = y;
}

GLfloat3::GLfloat3()
{

}

GLfloat3::GLfloat3( GLfloat x, GLfloat y, GLfloat z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

GLfloat4::GLfloat4()
{

}

GLfloat4::GLfloat4( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
