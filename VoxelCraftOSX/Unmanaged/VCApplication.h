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


using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	void Initialize(int argc, char** argv);
	void Run();

public:
    VCWindow* Window;
	VCGLRenderer* Renderer;
    VCSceneGraph* SceneGraph;
    VCInput* Input;
    VCTime* Time;
    VCObjectStore* ObjectStore;
    
    static VCApplication* Instance;

private:
    VCGameObject* m_testChunkGO;
    double m_lastDeltaTime;
    
    MonoDomain *m_pRootDomain;
	MonoImage *m_assemblyImage;
    
	MonoClass *m_engineType;
	MonoObject *m_engineInstance;
    
    MonoMethod* m_updateMethod;
    MonoMethod* m_lateUpdateMethod;
};

void SayHelloUnmanaged();
