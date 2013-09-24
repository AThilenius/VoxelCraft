//
//  Utilities.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include <string>
#include <iostream>
#include <glew.h>

#define glErrorCheck() _glErrorCheck("NoPrettyFunc"/*__PRETTY_FUNCTION__*/, __LINE__);
void _glErrorCheck(std::string file, int line);
unsigned long FastRandom();