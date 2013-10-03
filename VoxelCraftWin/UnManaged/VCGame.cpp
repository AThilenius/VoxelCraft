//
//  Game.cpp
//  Engine
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGame.h"
#include "VCWindow.h"
#include "VCInput.h"

VCGame::VCGame()
{
    
}

VCGame::~VCGame()
{
    
}

void VCGame::Initalize()
{    
    VCApplication::Initialize();
}

void VCGame::Run()
{   
	VCWindow::Instance->SetVSync(false);

	while(!glfwGetKey(VCWindow::Instance->GLFWWindowHandle, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(VCWindow::Instance->GLFWWindowHandle) )
    {
    }
}