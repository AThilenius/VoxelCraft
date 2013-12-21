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

void VCApplication::ShutDown()
{
    glfwTerminate();
}

VCApplication* g_headApp = 0;

void VCInteropInitalizeWindow()
{
	VCApplication::Instance = new VCApplication();
	VCApplication::Instance->Window = new VCWindow();
	VCApplication::Instance->Window->Initalize();
}

void VCInteropInitalizeObjectStore()
{
	VCApplication::Instance->ObjectStore = new VCObjectStore();
	VCApplication::Instance->ObjectStore->Initalize();
}

void VCInteropInitalizeInput()
{
	VCApplication::Instance->Input = new VCInput();
	VCApplication::Instance->Input->Initalize();
}

void VCInteropInitalizeRenderer()
{
	VCApplication::Instance->Renderer = new VCGLRenderer();
	VCApplication::Instance->Renderer->Initialize();
}

void VCInteropInitalizeLexEngine()
{
	VCApplication::Instance->LexEngine = new VCLexicalEngine();
	VCApplication::Instance->LexEngine->Initialize();
}

void VCInteropInitalizeGui()
{
	VCApplication::Instance->Gui = new VCGui();
	VCApplication::Instance->Gui->Initialize();
}

void VCInteropInitalizeSceneGraph()
{
	VCApplication::Instance->SceneGraph = new VCSceneGraph();
	VCApplication::Instance->SceneGraph->Initalize();
}
