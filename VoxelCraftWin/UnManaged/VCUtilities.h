//
//  VCUtilities.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// OpenGL
#ifdef __FUNCTION__
#define _FNAME_ __FUNCTION__
#endif

#ifdef __PRETTY_FUNCTION__
#define _FNAME_ __PRETTY_FUNCTION__
#endif

#ifndef _FNAME_
#define _FNAME_ "No function macro found"
#endif

#define glErrorCheck() _glErrorCheck(_FNAME_, __LINE__);
void _glErrorCheck(std::string file, int line);

// Math
unsigned long FastRandom();
#define FAST_FLOOR(f) f >= 0 ? (int) f : (int) f - 1;

// Console
enum ConsoleColor { White, Red, Yellow, Green, Blue };
void SetConsoleColor ( ConsoleColor color );

// Runtime Constraints
template<class T, class B> 
struct Derived_from 
{
	static void constraints(T* p) { B* pb = p; }
	Derived_from() { void(*p)(T*) = constraints; }
};

template<class T1, class T2> 
struct Can_copy 
{
	static void constraints(T1 a, T2 b) { T2 c = a; b = a; }
	Can_copy() { void(*p)(T1,T2) = constraints; }
};

template<class T1, class T2 = T1> 
struct Can_compare 
{
	static void constraints(T1 a, T2 b) { a==b; a!=b; a<b; }
	Can_compare() { void(*p)(T1,T2) = constraints; }
};

template<class T1, class T2, class T3 = T1> 
struct Can_multiply 
{
	static void constraints(T1 a, T2 b, T3 c) { c = a*b; }
	Can_multiply() { void(*p)(T1,T2,T3) = constraints; }
};