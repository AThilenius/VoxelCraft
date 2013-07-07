#pragma once
#import <string>
#import <iostream>
#include <GL/glew.h>

#define glErrorCheck() _glErrorCheck(__PRETTY_FUNCTION__, __LINE__);
void _glErrorCheck(std::string file, int line);
unsigned long FastRandom();