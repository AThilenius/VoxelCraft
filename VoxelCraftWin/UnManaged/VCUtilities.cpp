//
//  VCUtilities.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCUtilities.h"

void _glErrorCheck(std::string file, int line)
{
#ifdef DEBUG
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
        
		//std::string errStr("-[ %s ]- Line: %i - %s\n", file.c_str(), line, str);
		VC_ERROR("-[ " << file << " ]- Line: " << line << " - " << str);
        errCode = glGetError();
	}

#endif
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

std::string LoadTextFile (std::string path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		VC_ERROR("Failed to open file: " << path);
	}

	std::string ss;

	while (file.good())
	{
		char c = file.get();
		if (file.good())
			ss += c;
	}

	file.close();

	return ss;
}


// ================= OS X Macros ==========================================================================
#ifdef __APPLE__

void SetConsoleColor ( ConsoleColor color )
{
	switch ( color )
	{
	case White:
		std::std::cout << "\033[0m";
		break;

	case Red:
		std::std::cout << "\033[31m";
		break;

	case Yellow:
		std::std::cout << "\033[33m";
		break;

	case Green:
		std::std::cout << "\033[32m";
		break;

	case Blue:
		std::std::cout << "\033[36m";
		break;
	}
}

// ================= Windows Macros =======================================================================
#elif defined _WIN32 || defined _WIN64

#include <Windows.h>

void SetConsoleColor ( ConsoleColor color )
{

	switch ( color )
	{
	case White:
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		break;

	case Red:
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_RED|FOREGROUND_INTENSITY);
		break;

	case Yellow:
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
		break;

	case Green:
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;

	case Blue:
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE
			|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	}
}

#endif