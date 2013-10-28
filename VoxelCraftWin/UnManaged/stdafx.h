#pragma once

#define GLEW_STATIC
#define _CRT_SECURE_NO_DEPRECATE

// Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "mono.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3dll.lib")

// STD
#include <exception>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <regex>
#include <math.h>

// External
#include "glew.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

#include "VCTypes.h"
#include "Utilities.h"
#include "Constants.h"
#include "Macros.h"