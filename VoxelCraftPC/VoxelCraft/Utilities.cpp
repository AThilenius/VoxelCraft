#include "Utilities.h"

void glErrorCheck(char* beginMessage)
{
	GLenum errCode;
	errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("%s - OpenGL Error: %s\n", beginMessage, glewGetErrorString(errCode));
	}
}

unsigned long random() 
{
	static unsigned long x=123456789, y=362436069, z=521288629;

	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}