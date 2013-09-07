//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCApplication.h"

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

VCApplication* VCApplication::Instance;

VCApplication::VCApplication(void)
{
    VCApplication::Instance = this;
}

VCApplication::~VCApplication(void)
{
}

void VCApplication::Initialize()
{
    cout << "====================   VoxelCraft Engine Begin   ====================" << endl;
    
    Window = new VCWindow();
    Window->Initalize();
    
    ObjectStore = new VCObjectStore();
    ObjectStore->Initalize();
    
    Input = new VCInput();
    Input->Initalize();
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
    
    MonoRuntime = new VCMonoRuntime();
    MonoRuntime->Initalize();
    MonoRuntime->InvokeInitalize();
    
    // Test Chunk
    cout << "Creating test chunk..." << endl;
    VCChunk* testChunk = new VCChunk(0, 0, 0, NULL);
    testChunk->SetParent(VCSceneGraph::Instance->RootNode);
    
    testChunk->Generate();
    testChunk->StartRebuild();
    testChunk->ContinueRebuild(0.0f);
    
    MonoRuntime->InvokeStart();
}

void VCApplication::ShutDown()
{
    glfwTerminate();
}

void VCApplication::Step()
{
    Time->Update();
    Input->Update();
    
    MonoRuntime->InvokeUpdate();
    
    // Physics here...
    MonoRuntime->InvokeLateUpdate();
    
    MonoRuntime->InvokePreRender();
    Renderer->Render();
    SceneGraph->RenderGraph();
    
    // Framerate Check
    double framerate = 1.0f / VCTime::DeltaTime();
    framerate = framerate * 0.05f + m_lastDeltaTime * 0.95f;
    m_lastDeltaTime = framerate;
    stringstream ss;
    ss << "Voxel Craft - " /*<< setprecision(2)*/ << framerate << " FPS.";
    glfwSetWindowTitle( ss.str().c_str() );
    // ~Framerate Check
    
    glfwSwapBuffers();
    glfwPollEvents();
}

