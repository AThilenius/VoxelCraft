//
//  Game.cpp
//  Engine
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGame.h"

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
    // Disable VSync
    glfwSwapInterval(0);
    
    while(!VCInput::IsKeyDown(GLFW_KEY_ESC))
    {
        
        VCApplication::Step();
    }
}