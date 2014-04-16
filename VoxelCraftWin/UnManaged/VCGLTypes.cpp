//
//  VCGLTypes.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/12/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLTypes.h"


int VCGLPrimitives::RuntimeLookupTable[11] = {
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,
	GL_FLOAT,
	GL_2_BYTES,
	GL_3_BYTES,
	GL_4_BYTES,
	GL_DOUBLE
};

int VCGLDrawModes::RuntimeLookupTable[3] = {
	GL_STATIC_DRAW,
	GL_DYNAMIC_DRAW,
	GL_STREAM_DRAW
};

int VCGLDrawPrimitives::RuntimeLookupTable[12] = {
	GL_POINTS, 
	GL_LINE_STRIP, 
	GL_LINE_LOOP, 
	GL_LINES, 
	GL_LINE_STRIP_ADJACENCY, 
	GL_LINES_ADJACENCY, 
	GL_TRIANGLE_STRIP, 
	GL_TRIANGLE_FAN, 
	GL_TRIANGLES, 
	GL_TRIANGLE_STRIP_ADJACENCY, 
	GL_TRIANGLES_ADJACENCY,
	GL_PATCHES
};
