#pragma once

#import <GL/glew.h>
#import <GL/glfw.h>
#import <glm/glm.hpp>
#import <glm/ext.hpp>

//#include <glew.h>
//#include <glfw3.h>
//#include "glm/glm.hpp"
//#include "glm/ext.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
//#include <windows.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

#include "VCTime.h"
#include "VCTypes.h"
#include "Utilities.h"

using namespace std;


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

#define CONSOLE_COLOR_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#define CONSOLE_COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
#define CONSOLE_COLOR_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
#define CONSOLE_COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
#define CONSOLE_COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |FOREGROUND_GREEN|FOREGROUND_INTENSITY);



#else
#error "Unknown Platform!"
#endif



