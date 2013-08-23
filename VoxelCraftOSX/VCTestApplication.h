//
//  VCTestApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCTestApplication__
#define __VoxelCraftOSX__VCTestApplication__

#include "PCH.h"
#include "VCTestShader.h"


class VCTestApplication
{
public:
    VCTestApplication();
    ~VCTestApplication();
    
    void Initialize();
	void Run();
    
private:
    VCTestShader* m_testShader;
    GLuint m_bufferId;
};



#endif /* defined(__VoxelCraftOSX__VCTestApplication__) */
