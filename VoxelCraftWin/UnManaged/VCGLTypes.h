//
//  VCGLTypes.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/12/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct VCGLPrimitives
{
	enum Types
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		Byte2 = GL_2_BYTES,
		Byte3 = GL_3_BYTES,
		Byte4 = GL_4_BYTES,
		Double = GL_DOUBLE
	};
};

struct VCGLDrawModes
{
	enum Types
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW
	};
};