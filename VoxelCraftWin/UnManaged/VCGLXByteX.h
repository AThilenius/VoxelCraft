//
//  VCGLXByteX.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once


struct GLubyte3
{
	GLubyte3();
	GLubyte3(GLubyte x, GLubyte y, GLubyte z );

	GLubyte x;
	GLubyte y;
	GLubyte z;
};

struct GLbyte3
{
	GLbyte3();
	GLbyte3(GLbyte x, GLbyte y, GLbyte z );

	GLbyte x;
	GLbyte y;
	GLbyte z;
};

struct GLubyte4
{
	GLubyte4();
	GLubyte4(GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	GLubyte x;
	GLubyte y;
	GLubyte z;
	GLubyte w;

	GLubyte4 operator+(const GLubyte4&) const;
	GLubyte4 operator-(const GLubyte4&) const;
	GLubyte4 operator*(const glm::vec4&) const;
};

bool operator==(const GLubyte4& lhs, const GLubyte4& rhs);

struct GLbyte4
{
	GLbyte4();
	GLbyte4(GLbyte x, GLbyte y, GLbyte z, GLbyte w);

	GLbyte x;
	GLbyte y;
	GLbyte z;
	GLbyte w;
};
