//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCApplication.h"

#include "PCH.h"
#include "VCWorld.h"
#include "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"
#include "VCInput.h"
#include "VCSceneGraph.h"
#include "VCCamera.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"
#include "VCLexicalEngine.h"

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

	LexEngine = new VCLexicalEngine();
	LexEngine->Initialize();
	LexEngine->LoadFont("Cambria-32", "C:\\Users\\Alec\\Desktop\\BmpTests\\Binary.fnt", "C:\\Users\\Alec\\Desktop\\BmpTests\\Binary_0.DDS");
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
    
    MonoRuntime = new VCMonoRuntime();
    MonoRuntime->Initalize();
    MonoRuntime->InvokeInitalize();

	// Debug
	VCWorld* testWorld = new VCWorld(4);
	testWorld->Initialize();

    
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

