//
//  stdafx.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

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
#pragma comment(lib, "SOIL.lib")

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
#include <regex>
#include <math.h>
#include <stdint.h>
#include <memory>

// External
#include "glew.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SOIL.h"

#include "VCGLXByteX.h"
#include "VCGLXShortX.h"
#include "VCGLFloatX.h"
#include "VCGeometryTypes.h"
#include "VCXIntX.h"
#include "VCTypeDefs.h"
#include "VCUtilities.h"
#include "VCConstants.h"
#include "VCMacros.h"