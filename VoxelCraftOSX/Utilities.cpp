#include "Utilities.h"

void _glErrorCheck(std::string file, int line)
{
	GLenum errCode;
	errCode = glGetError();
	while (errCode != GL_NO_ERROR)
	{
		printf("-[ %s ]- Line: %i - %s\n", file.c_str(), line, glewGetErrorString(errCode));
        errCode = glGetError();
	}
}

unsigned long FastRandom() 
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