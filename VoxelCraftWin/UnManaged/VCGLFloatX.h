//
//  VCGLFloatX.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct GLfloat2
{
	GLfloat2();
	GLfloat2(GLfloat x, GLfloat y );

	GLfloat x;
	GLfloat y;
};

struct GLfloat3
{
	GLfloat3();
	GLfloat3(GLfloat x, GLfloat y, GLfloat z );

	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct GLfloat4
{
	GLfloat4();
	GLfloat4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};