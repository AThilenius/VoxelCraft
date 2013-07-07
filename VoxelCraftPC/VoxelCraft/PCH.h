#pragma once

#include <glew.h>
#include <glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "VCTime.h"
#include "VCTypes.h"

#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <windows.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>


// ================= Constants ===========================================================================

// RENDERING
#define VC_ATTRIBUTE_POSITION 0 
#define VC_ATTRIBUTE_NORMAL 1
#define VC_ATTRIBUTE_COLOR 2

#define BLOCK_RENDER_SIZE 1.0f

// WORLD
#define VIEW_DISTANCE 8
#define VIEW_DISTANCE_TWO 16
#define LOG_VIEW_DIST_TWO 4

// CHUNK
#define CHUNK_WIDTH 64
#define CHUNK_TOTAL_COUNT 262144

#define LOG_CHUNK_WIDTH 6
#define MASK_CHUNK_WIDTH 63


// ================= Macros ===============================================================================
#define POSITIVE_CHECK(value) if(value < 0) { throw new std::exception("Positive Check Failed!"); }
#define ZERO_CHECK(value) if(value == 0) { throw new std::exception("Zero Check Failed!"); }


#define CONSOLE_COLOR_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#define CONSOLE_COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
#define CONSOLE_COLOR_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);		
#define CONSOLE_COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
#define CONSOLE_COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |FOREGROUND_GREEN|FOREGROUND_INTENSITY);

#define FOREACH(iterName, variable) for (auto iterName = variable.begin(); iterName != variable.end(); iterName++)

//#define FLATTEN(X,Y,Z) Z + CHUNK_WIDTH * (Y + CHUNK_HEIGHT * X)
//#define FLATTEN_CHUNK(X,Y,Z) ((((X << LOG_CHUNK_WIDTH) + Y) << LOG_CHUNK_WIDTH ) + Z)
//#define FLATTEN_WORLD(X,Y,Z) ((((X << LOG_VIEW_DIST_TWO) + Y) << LOG_VIEW_DIST_TWO ) + Z)

// Z -> X -> Y memory access pattern
#define FLATTEN_CHUNK(X,Y,Z) ((((Z << LOG_CHUNK_WIDTH) + X) << LOG_CHUNK_WIDTH ) + Y)

// ================= Inline ===============================================================================

inline void glErrorCheck(char* beginMessage)
{
	GLenum errCode;
	errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("%s - OpenGL Error: %s\n", beginMessage, glewGetErrorString(errCode));
	}
}



inline unsigned long randomLong()
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