//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCInput.h"
#include "VCWindow.h"

VCInput* VCInput::Instance;

VCInput::VCInput()
{
    VCInput::Instance = this;
    
    m_keysDown = (char*) malloc(sizeof(char) * 325);
    
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
void KeyHanlder( GLFWwindow* window, int key, int scancode, int action, int mods  )
{   
    VCInput::Instance->m_keysDown[key] = action;
}

void MouseButtonHanlder(GLFWwindow* window, int button, int action, int mod )
{
    VCInput::Instance->m_mouseButtonsDown[button] = action;
}

void VCInput::Initalize()
{
    // Register Handlers
	glfwSetKeyCallback(VCWindow::Instance->GLFWWindowHandle, KeyHanlder);
	glfwSetMouseButtonCallback(VCWindow::Instance->GLFWWindowHandle, MouseButtonHanlder);
    
	glfwSetInputMode(VCWindow::Instance->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    cout << "VCInput Initalized" << endl;
}

void VCInput::Update()
{
    double x, y;
	double width = VCWindow::Instance->Width;
	double height = VCWindow::Instance->Height;

    //glfwSetMousePos(width / 2, height / 2);
	glfwGetCursorPos(VCWindow::Instance->GLFWWindowHandle, &x, &y);
	glfwSetCursorPos(VCWindow::Instance->GLFWWindowHandle, (float)width * 0.5f, (float)height * 0.5f);
    
    VCInput::Instance->m_deltaX = (float)(width / 2.0f - x) / width;
    VCInput::Instance->m_deltaY = (float)(height / 2.0f - y) / height;
}

bool VCInput::IsKeyDown ( int keycode )
{
    return VCInput::Instance->m_keysDown[keycode] != 0;
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


// ================================      Interop      ============
void VCInput::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Input::VCInteropInputGetMouse",    (void*)VCInteropInputGetMouse);
    mono_add_internal_call("VCEngine.Input::VCInteropInputGetKeys",     (void*)VCInteropInputGetKeys);
}

void VCInteropInputGetMouse(float* x, float* y, bool* left, bool* right)
{
    *x = VCInput::Instance->m_deltaX;
    *y = VCInput::Instance->m_deltaY;
    *left = VCInput::Instance->m_mouseButtonsDown[0];
    *right = VCInput::Instance->m_mouseButtonsDown[0];
}

int* VCInteropInputGetKeys()
{
    return (int*) VCInput::Instance->m_keysDown;
}


