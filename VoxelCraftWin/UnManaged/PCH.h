//
//  PCH.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// Glew, Glfw, GLM
#include "glew.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// STD
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

// Mono
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

// User
#include "VCTime.h"
#include "VCInput.h"
#include "VCTypes.h"
#include "Utilities.h"
#include "VCObjectStore.h"

using namespace std;
using namespace glm;

class VCInput;

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
#define ZERO_CHECK(value) if(value == 0) { std::cout << "Zero Check Failed!" << std::endl; }
#define FOREACH(iterName, variable) for (auto iterName = variable.begin(); iterName != variable.end(); iterName++)

// Z -> X -> Y memory access pattern
#define FLATTEN_CHUNK(X,Y,Z) ((((Z << LOG_CHUNK_WIDTH) + X) << LOG_CHUNK_WIDTH ) + Y)



// ================= OS X Macros ==========================================================================
#ifdef __APPLE__

#define CONSOLE_COLOR_WHITE 
#define CONSOLE_COLOR_RED 
#define CONSOLE_COLOR_YELLOW
#define CONSOLE_COLOR_GREEN
#define CONSOLE_COLOR_BLUE


// ================= Windows Macros =======================================================================
#elif defined _WIN32 || defined _WIN64

//#include <windows.h>
//
//#define CONSOLE_COLOR_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
//#define CONSOLE_COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
//#define CONSOLE_COLOR_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
//#define CONSOLE_COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
//#define CONSOLE_COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |FOREGROUND_GREEN|FOREGROUND_INTENSITY);

#define CONSOLE_COLOR_WHITE 
#define CONSOLE_COLOR_RED 
#define CONSOLE_COLOR_YELLOW
#define CONSOLE_COLOR_GREEN
#define CONSOLE_COLOR_BLUE



#else
#error "Unknown Platform!"
#endif



