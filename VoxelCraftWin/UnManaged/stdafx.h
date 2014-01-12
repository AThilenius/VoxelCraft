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
#define _SCL_SECURE_NO_WARNINGS
#define SRUTIL_DELEGATE_PREFERRED_SYNTAX

// Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "mono.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "assimp.lib")

#pragma comment(lib, "PhysX3CHECKED_x86.lib")
#pragma comment(lib, "PhysX3CommonCHECKED_x86.lib")
#pragma comment(lib, "PhysX3CharacterKinematicCHECKED_x86.lib")
#pragma comment(lib, "PhysX3CookingCHECKED_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsCHECKED.lib")
#pragma comment(lib, "PhysX3VehicleCHECKED.lib")
#pragma comment(lib, "PhysXProfileSDKCHECKED.lib")
#pragma comment(lib, "PhysXVisualDebuggerSDKCHECKED.lib")
#pragma comment(lib, "PxTaskCHECKED.lib")

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
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>

// External
#include "glew.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SOIL.h"
#include <boost/container/flat_set.hpp>

#include "VCGLXByteX.h"
#include "VCGLXShortX.h"
#include "VCGLFloatX.h"
#include "VCGeometryTypes.h"
#include "VCXIntX.h"
#include "VCFloatX.h"
#include "VCUtilities.h"
#include "VCConstants.h"
#include "VCMacros.h"
#include "delegate.hpp"

// Typedefs
#include "VCTypeDefs.h"