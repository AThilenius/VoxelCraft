//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCApplication.h"

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

void VCApplication::ShutDown()
{
    glfwTerminate();
}

VCApplication* g_headApp = 0;

DLL_EXPORT_API void VCInteropInitalizeApplication()
{
	g_headApp = new VCApplication();
	g_headApp->Initialize();
}
