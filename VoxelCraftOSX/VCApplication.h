//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"
#include "VCInput.h"

using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	void Initialize();
	void Run();

public:
	VCGLRenderer* Renderer;
	VCGameObject* RootNode;
    VCInput* Input;
    VCTime* Time;
    
    static VCApplication* Instance;

private:
    VCChunk* m_testChunk;
};

