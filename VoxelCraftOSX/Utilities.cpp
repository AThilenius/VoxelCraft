//
//  Utilities.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "Utilities.h"

void _glErrorCheck(std::string file, int line)
{
	GLenum errCode;
	errCode = glGetError();
	while (errCode != GL_NO_ERROR)
	{   
        const char *str;
        switch( errCode )
        {
            case GL_NO_ERROR:
                str = "GL_NO_ERROR";
                break;
            case GL_INVALID_ENUM:
                str = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                str = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                str = "GL_INVALID_OPERATION";
                break;
#if defined __gl_h_ || defined __gl3_h_
            case GL_OUT_OF_MEMORY:
                str = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                str = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
#endif
#if defined __gl_h_
            case GL_STACK_OVERFLOW:
                str = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                str = "GL_STACK_UNDERFLOW";
                break;
            case GL_TABLE_TOO_LARGE:
                str = "GL_TABLE_TOO_LARGE";
                break;
#endif
            default:
                str = "(ERROR: Unknown Error Enum)";
                break;
        }
        
        
		printf("-[ %s ]- Line: %i - %s\n", file.c_str(), line, str);
        errCode = glGetError();
	}
}

unsigned long FastRandom() 
{
	static unsigned long x=123456789, y=362436069, z=521288629;

	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}