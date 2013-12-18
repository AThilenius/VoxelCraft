//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCApplication.h"
#include "VCInteropInvoke.h"

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
    std::cout << "====================   VoxelCraft Engine Begin   ====================" << std::endl;

	MonoRuntime = new VCMonoRuntime();
	MonoRuntime->Initalize();

    Window = new VCWindow();
    Window->Initalize();
    
    ObjectStore = new VCObjectStore();
    ObjectStore->Initalize();
    
    Input = new VCInput();
    Input->Initalize();
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();

	LexEngine = new VCLexicalEngine();
	LexEngine->Initialize();

	Gui = new VCGui();
	Gui->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
}

void VCApplication::EditorMain()
{
	//MonoRuntime->EditorMain();
	VCInteropInvoke::EditorEntry();
}

void VCApplication::GameMain()
{
	//MonoRuntime->GameMain();
}

void VCApplication::ShutDown()
{
    glfwTerminate();
}