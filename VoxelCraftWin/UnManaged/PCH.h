//
//  PCH.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// Switches
//#define GLEW_STATIC
//#define _CRT_SECURE_NO_DEPRECATE


// STD
//#include <exception>
//#include <iostream>
//#include <iomanip>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string>
//#include <sstream>
//#include <cstring>
//#include <fstream>
//#include <vector>
//#include <unordered_map>
//#include <unordered_set>
//#include <map>
//#include <set>
//#include <regex>
//#include <math.h>

// Glew, Glfw, GLM
//#include "glew.h"
//#include "glfw3.h"
//#include "glm/glm.hpp"
//#include "glm/ext.hpp"

// Mono
//#include <mono/mini/jit.h>
//#include <mono/metadata/assembly.h>
//#include <mono/metadata/mono-debug.h>
//#include <mono/metadata/debug-helpers.h>
//#include <mono/metadata/appdomain.h>
//#include <mono/metadata/object.h>
//#include <mono/metadata/threads.h>
//#include <mono/metadata/environment.h>
//#include <mono/metadata/mono-gc.h>

// User
//#include "VCMonoString.h"
//#include "VCTypes.h"
//#include "Utilities.h"
//#include "VCObjectStore.h"

//using namespace std;
using namespace glm;

//class VCInput;

//// ================= Constants ===========================================================================
//
//// RENDERING
//#define VC_ATTRIBUTE_POSITION 0
//#define VC_ATTRIBUTE_NORMAL 1
//#define VC_ATTRIBUTE_COLOR 2
//#define VC_ATTRIBUTE_TEX_COORD_0 3
//
//#define BLOCK_RENDER_SIZE 1.0f
//
//// WORLD
//#define VIEW_DISTANCE 2
//#define VIEW_DISTANCE_TWO 4
//#define LOG_VIEW_DIST_TWO 2
//
//// CHUNK
//#define CHUNK_WIDTH 32
//#define CHUNK_TOTAL_COUNT 32768
//
//#define LOG_CHUNK_WIDTH 5
//#define MASK_CHUNK_WIDTH 31
//
//
//// ================= Macros ===============================================================================
//#define POSITIVE_CHECK(value) if(value < 0) { SetConsoleColor(Red); std::cout << "Positive Check Failed!" << std::endl; SetConsoleColor(White); cin.clear(); cin.ignore(); }
//#define ZERO_CHECK(value) if(value == 0) { SetConsoleColor(Red); std::cout << "Zero Check Failed!" << std::endl; SetConsoleColor(White); cin.clear(); cin.ignore(); }
//#define FOREACH(iterName, variable) for (auto iterName = variable.begin(); iterName != variable.end(); iterName++)
//#define VC_ERROR(message) SetConsoleColor(Red); std::cout << message << std::endl; SetConsoleColor(White); cin.clear(); cin.ignore();
//
//// Z -> X -> Y memory access pattern
//#define FLATTEN_CHUNK(X,Y,Z) ((((Z << LOG_CHUNK_WIDTH) + X) << LOG_CHUNK_WIDTH ) + Y)
//#define FLATTEN_2D(X,Z,WIDTH) ((X << WIDTH) + Z)
//
//#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
//	TypeName(const TypeName&);   \
//	void operator=(const TypeName&)
//
//// ================= OS X Macros ==========================================================================
//#ifdef __APPLE__
//
//// ================= Windows Macros =======================================================================
//#elif defined _WIN32 || defined _WIN64
//
//
//
//
//#else
//#error "Unknown Platform!"
//#endif



