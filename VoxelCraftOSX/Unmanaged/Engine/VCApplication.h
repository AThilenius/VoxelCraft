//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#import "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"
#include "VCInput.h"
#import "VCSceneGraph.h"
#import "VCCamera.h"
#import "VCObjectStore.h"
#import "VCMonoRuntime.h"


using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	virtual void Initialize();
    virtual void Step();

public:
    VCWindow* Window;
	VCGLRenderer* Renderer;
    VCSceneGraph* SceneGraph;
    VCInput* Input;
    VCTime* Time;
    VCObjectStore* ObjectStore;
    VCMonoRuntime* MonoRuntime;
    
    static VCApplication* Instance;

private:
    VCGameObject* m_testChunkGO;
    double m_lastDeltaTime;
    

};

void SayHelloUnmanaged();
