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

GLubyte4::GLubyte4():
	x(0),
	y(0),
	z(0),
	w(0)
{

}

GLubyte4::GLubyte4( GLubyte x, GLubyte y, GLubyte z, GLubyte w ):
	x(x),
	y(y),
	z(z),
	w(w)
{
}

GLubyte4 GLubyte4::operator+( const GLubyte4& o ) const
{
	return GLubyte4 (
		((int)x + (int)o.x) >= 255 ? 255 : x + o.x,
		((int)y + (int)o.y) >= 255 ? 255 : y + o.y,
		((int)z + (int)o.z) >= 255 ? 255 : z + o.z,
		((int)w + (int)o.w) >= 255 ? 255 : w + o.w );
}

GLubyte4 GLubyte4::Lerp( const GLubyte4& from, const GLubyte4& to, float ammount )
{
	if (ammount == 0.0f)
		return from;

	if (ammount == 1.0f)
		return to;

	return GLubyte4 (
		(int)(from.x + (to.x - from.x) * ammount),
		(int)(from.y + (to.y - from.y) * ammount),
		(int)(from.z + (to.z - from.z) * ammount),
		(int)(from.w + (to.w - from.w) * ammount));
}

void GLubyte4::Lerp( GLubyte4& value, const GLubyte4& from, const GLubyte4& to, float ammount )
{
	value.x = (int)(from.x + (to.x - from.x) * ammount);
	value.y = (int)(from.y + (to.y - from.y) * ammount);
	value.z = (int)(from.z + (to.z - from.z) * ammount);
	value.w = (int)(from.w + (to.w - from.w) * ammount);
}

GLubyte4 GLubyte4::operator-( const GLubyte4& o ) const
{
	return GLubyte4 (
		((int)x - (int)o.x) <= 0 ? 0 : x - o.x,
		((int)y - (int)o.y) <= 0 ? 0 : y - o.y,
		((int)z - (int)o.z) <= 0 ? 0 : z - o.z,
		((int)w - (int)o.w) <= 0 ? 0 : w - o.w );
}

GLubyte4 GLubyte4::operator*( const glm::vec4& o) const
{
	float xf = (float)x * o.x;
	float yf = (float)y * o.y;
	float zf = (float)z * o.z;
	float wf = (float)w * o.w;

	if (xf < 0)			xf = 0;
	else if (xf >= 255) xf = 255;

	if (yf < 0)			yf = 0;
	else if (yf >= 255) yf = 255;

	if (zf < 0)			zf = 0;
	else if (zf >= 255) zf = 255;

	if (wf < 0)			wf = 0;
	else if (wf >= 255) wf = 255;

	return GLubyte4 ( (int)xf, (int)yf, (int)zf, (int)wf );
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
