//
//  Macros.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// =====   General   ======================================================
#define POSITIVE_CHECK(value) if(value < 0) { SetConsoleColor(Red); cout << "Positive Check Failed!" << endl; SetConsoleColor(White); cin.clear(); cin.ignore(); }
#define ZERO_CHECK(value) if(value == 0) { SetConsoleColor(Red); cout << "Zero Check Failed!" << endl; SetConsoleColor(White); cin.clear(); cin.ignore(); }
#define FOREACH(iterName, variable) for (auto iterName = variable.begin(); iterName != variable.end(); iterName++)
#define VC_ERROR(message) SetConsoleColor(Red); cout << message << endl; SetConsoleColor(White); cin.clear(); cin.ignore();

// Z -> X -> Y memory access pattern
#define FLATTEN_CHUNK(X,Y,Z) ((((Z << LOG_CHUNK_WIDTH) + X) << LOG_CHUNK_WIDTH ) + Y)
#define FLATTEN_2D(X,Z,WIDTH) ((X << WIDTH) + Z)

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);   \
	void operator=(const TypeName&)

// ================= OS X Macros ==========================================================================
#ifdef __APPLE__

// ================= Windows Macros =======================================================================
#elif defined _WIN32 || defined _WIN64




#else
#error "Unknown Platform!"
#endif