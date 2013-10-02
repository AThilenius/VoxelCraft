//
//  Utilities.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include <string>
#include <iostream>
#include <glew.h>

// OpenGL
#ifdef __FUNCTION__
#define _FNAME_ __FUNCTION__
#endif

#ifdef __PRETTY_FUNCTION__
#define _FNAME_ __PRETTY_FUNCTION__
#endif

#ifndef _FNAME_
#define _FNAME_ "No funtion macro found"
#endif

#define glErrorCheck() _glErrorCheck(_FNAME_, __LINE__);
void _glErrorCheck(std::string file, int line);
unsigned long FastRandom();

// Math
#define FAST_FLOOR(f) f >= 0 ? (int) f : (int) f - 1;


enum ConsoleColor { White, Red, Yellow, Green, Blue };
void SetConsoleColor ( ConsoleColor color );