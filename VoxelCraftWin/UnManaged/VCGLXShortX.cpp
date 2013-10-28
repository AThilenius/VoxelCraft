//
//  VCGLXShortX.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLXShortX.h"

GLshort3::GLshort3()
{

}

GLshort3::GLshort3( GLshort x, GLshort y, GLshort z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

GLushort2::GLushort2()
{

}

GLushort2::GLushort2( GLushort x, GLushort y ) : 
	x(x),
	y(y)
{

}

GLushort3::GLushort3()
{

}

GLushort3::GLushort3( GLushort x, GLushort y, GLushort z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}
