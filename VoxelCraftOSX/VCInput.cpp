//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCInput.h"

VCInput* VCInput::Instance;

VCInput::VCInput()
{
    VCInput::Instance = this;
    
    for ( int i = 0; i < 350; i ++ )
        m_keysDown[i] = false;
    
    for ( int i = 0; i < 10; i++ )
        m_mouseButtonsDown[i] = false;
    
    m_deltaX = 0.0f;
    m_deltaY = 0.0f;
}

VCInput::~VCInput()
{
    
}

// Range 0 - 352
void GLFWCALL KeyHanlder( int key, int action )
{   
    VCInput::Instance->m_keysDown[key] = action;
}

void GLFWCALL MouseButtonHanlder( int button, int action )
{
    VCInput::Instance->m_mouseButtonsDown[button] = action;
}

void VCInput::Initalize()
{
    // Register Hanlders
    glfwSetKeyCallback(KeyHanlder);
    glfwSetMouseButtonCallback(MouseButtonHanlder);
    glfwDisable(GLFW_MOUSE_CURSOR);
    
    cout << "VCInput Initalized" << endl;
}

void VCInput::Update()
{
    int x, y, width, height;
    glfwGetWindowSize(&width, &height);
    glfwGetMousePos(&x, &y);
    glfwSetMousePos(width / 2, height / 2);
    
    VCInput::Instance->m_deltaX = (float)(width / 2 - x) / (float)width;
    VCInput::Instance->m_deltaY = (float)(height / 2 - y) / (float)height;
}

bool VCInput::IsKeyDown ( int keycode )
{
    return VCInput::Instance->m_keysDown[keycode];
}

void VCInput::GetMouse ( float* x, float* y )
{
    *x = -VCInput::Instance->m_deltaX;
    *y = VCInput::Instance->m_deltaY;
}

glm::vec2 VCInput::GetMouse2()
{
    return vec2 (-VCInput::Instance->m_deltaX, VCInput::Instance->m_deltaY);
}

glm::vec3 VCInput::GetMouse3()
{
    return vec3 (-VCInput::Instance->m_deltaX, VCInput::Instance->m_deltaY, 0.0f);
}

glm::vec3 VCInput::GetStrafe()
{
    vec3 ret;
    
    if ( VCInput::IsKeyDown('W') )
        ret.z += 1.0f;
    
    if ( VCInput::IsKeyDown('S') )
        ret.z -= 1.0f;
    
    if ( VCInput::IsKeyDown('A') )
        ret.x += 1.0f;
    
    if ( VCInput::IsKeyDown('D') )
        ret.x -= 1.0f;
    
    return ret;
}

bool VCInput::IsMouseDown ( int buttonID )
{
    return VCInput::Instance->m_mouseButtonsDown[buttonID];
}
