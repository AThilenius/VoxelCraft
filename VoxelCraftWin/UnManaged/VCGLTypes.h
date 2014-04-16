//
//  VCGLTypes.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/12/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// VCGLMarshaledBuffer needs to be updated if these are changed!


/************************************************************************/
/* Wraps a GL Type ( Ex. Byte, Float... )                               */
/************************************************************************/
struct VCGLPrimitives
{
	enum Types
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		Byte2 = GL_2_BYTES,
		Byte3 = GL_3_BYTES,
		Byte4 = GL_4_BYTES,
		Double = GL_DOUBLE
	};

	static int RuntimeLookupTable[11];
};

/************************************************************************/
/* The GL Draw mode, Static, Dynamic or Streamed                        */
/************************************************************************/
struct VCGLDrawModes
{
	enum Types
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
		Stream = GL_STREAM_DRAW
	};

	static int RuntimeLookupTable[3];
};

/************************************************************************/
/* Wraps the GL Draw Primitive type ( Ex. Point, Strip... )             */
/************************************************************************/
struct VCGLDrawPrimitives
{
	enum Types
	{
		Points = GL_POINTS, 
		LineStrip = GL_LINE_STRIP, 
		LineLoop = GL_LINE_LOOP, 
		LInes = GL_LINES, 
		LineStripAdjaceny = GL_LINE_STRIP_ADJACENCY, 
		LinesAdjacency = GL_LINES_ADJACENCY, 
		TriangleStrip = GL_TRIANGLE_STRIP, 
		TriangleFan = GL_TRIANGLE_FAN, 
		Triangles = GL_TRIANGLES, 
		TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY, 
		TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
		Patches = GL_PATCHES
	};

	static int RuntimeLookupTable[12];
};