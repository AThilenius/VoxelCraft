//
//  VMTestShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VMTestShader__
#define __VoxelCraftOSX__VMTestShader__

#include <iostream>
#include "Shader.h"
#include "PCH.h"

class VCTestShader : public Shader
{
public:
    VCTestShader();
    ~VCTestShader();
    
protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();
};

#endif /* defined(__VoxelCraftOSX__VMTestShader__) */
