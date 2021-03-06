//
//  VCMacros.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// =====   Export   ======================================================
#define DLL_EXPORT_API extern "C" __declspec(dllexport)

// =====   General   ======================================================
#define POSITIVE_CHECK(value) if(value < 0) { SetConsoleColor(Red); std::cout << "Positive Check Failed!" << std::endl; SetConsoleColor(White); std::cin.clear(); std::cin.ignore(); }
#define ZERO_CHECK(value) if(value == 0) { SetConsoleColor(Red); std::cout << "Zero Check Failed!" << std::endl; SetConsoleColor(White); std::cin.clear(); std::cin.ignore(); }
#define FOREACH(iterName, variable) for (auto iterName = variable.begin(); iterName != variable.end(); iterName++)
#define VC_ERROR(message) SetConsoleColor(Red); std::cout << message << std::endl; SetConsoleColor(White); std::cin.clear(); std::cin.ignore();
#define VC_WARN(message) SetConsoleColor(Yellow); std::cout << message << std::endl; SetConsoleColor(White);
#define VC_UNIFORM_DNE 0xffffffff

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