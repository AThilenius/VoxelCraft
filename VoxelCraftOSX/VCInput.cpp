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
    
    m_mouseX = 0;
    m_mouseY = 0;
}

VCInput::~VCInput()
{
    
}

// Range 0 - 352
void GLFWCALL KeyHanlder( int key, int action )
{
    VCInput::Instance->m_keysDown[key] = action;
}

void GLFWCALL MouseMoveHandler( int x, int y )
{
    VCInput::Instance->m_mouseX = x;
    VCInput::Instance->m_mouseY = y;
}

void GLFWCALL MouseButtonHanlder( int button, int action )
{
    VCInput::Instance->m_mouseButtonsDown[button] = action;
}

void VCInput::Initalize()
{
    // Register Hanlders
    glfwSetKeyCallback(KeyHanlder);
    glfwSetMousePosCallback(MouseMoveHandler);
    glfwSetMouseButtonCallback(MouseButtonHanlder);
}

bool VCInput::IsKeyDown ( int keycode )
{
    return VCInput::Instance->m_keysDown[keycode];
}

void VCInput::GetMouseLocation ( int* x, int* y )
{
    *x = VCInput::Instance->m_mouseX;
    *y = VCInput::Instance->m_mouseY;
}

bool VCInput::IsMouseDown ( int buttonID )
{
    return VCInput::Instance->m_mouseButtonsDown[buttonID];
}
