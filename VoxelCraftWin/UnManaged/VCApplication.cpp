//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCApplication.h"

#include "PCH.h"
#include "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"
#include "VCInput.h"
#include "VCSceneGraph.h"
#include "VCCamera.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"

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
    testChunk->Rebuild();
    
    MonoRuntime->InvokeStart();
}

void VCApplication::ShutDown()
{
    glfwTerminate();
}

void VCApplication::Step()
{
	// PreFrame
    Time->Update();
    Input->Update();
    
	// Mono
    MonoRuntime->InvokeUpdate();
    MonoRuntime->InvokeLateUpdate();
    MonoRuntime->InvokePreRender();

	// Rendering
    Renderer->Render();

	// Windowing
	Window->SwapBuffers();
}

