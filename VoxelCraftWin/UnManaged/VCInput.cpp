//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCInput.h"
#include "VCWindow.h"
#include "VCMonoRuntime.h"
#include "VCMonoMethod.h"

VCMonoMethod* VCInput::KeyCallback;
VCMonoMethod* VCInput::CharCallback;
VCMonoMethod* VCInput::MouseScrollCallback;
VCMonoMethod* VCInput::MouseEnterCallback;
VCMonoMethod* VCInput::MouseClickCallback;
VCMonoMethod* VCInput::MouseMoveCallback;


void _GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//void* args[4] = { &key, &scancode, &action, &mods };
	//VCInput::KeyCallback->Invoke(args);
}

void _GlfwCharCallback(GLFWwindow* window, unsigned int charCode)
{
	//void* args[1] = { &charCode };
	//VCInput::CharCallback->Invoke(args);
}

void _GlfwMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	//void* args[2] = { &x, &y };
	//VCInput::MouseMoveCallback->Invoke(args);
}

void _GlfwMouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	//void* args[3] = { &button, &action, &mods };
	//VCInput::MouseClickCallback->Invoke(args);
}

void _GlfwMouseEnterCallback(GLFWwindow* window, int entered)
{
	//void* args[1] = { &entered };
	//VCInput::MouseEnterCallback->Invoke(args);
}

void _GlfwMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	//void* args[2] = { &xOffset, &yOffset };
	//VCInput::MouseScrollCallback->Invoke(args);
}


VCInput::VCInput()
{
}

VCInput::~VCInput()
{
    
}

void VCInput::Initalize()
{
	// Get mono methods
	//VCInput::MouseScrollCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwMouseScrollCallback(double,double)");
	//VCInput::MouseEnterCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwMouseEnterCallback(int)");
	//VCInput::MouseClickCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwMouseClickCallback(int,int,int)");
	//VCInput::MouseMoveCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwMouseMoveCallback(double,double)");
	//VCInput::CharCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwCharCallback(int)");
	//VCInput::KeyCallback = VCMonoRuntime::GetMonoMethod("GlfwInputState", "GlfwKeyCallback(int,int,int,int)");

	glfwSetScrollCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseScrollCallback);
	glfwSetCursorEnterCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseEnterCallback);
	glfwSetMouseButtonCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseClickCallback);
	glfwSetCursorPosCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseMoveCallback);
	glfwSetCharCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwCharCallback);
	glfwSetKeyCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwKeyCallback);

	// Set initial mouse position
	double x, y;
	glfwGetCursorPos(VCWindow::Instance->GLFWWindowHandle, &x, &y);
	_GlfwMouseMoveCallback(VCWindow::Instance->GLFWWindowHandle, x, y);
}

// ================================      Interop      ============
void VCInput::RegisterMonoHandlers()
{
    VCMonoRuntime::SetMethod("GlfwInputState::VCInteropInputSetMouse",			(void*)VCInteropInputSetMouse);
	VCMonoRuntime::SetMethod("GlfwInputState::VCInteropInputSetCursorVisible",    (void*)VCInteropInputSetCursorVisible);
}

void VCInteropInputSetMouse(float x, float y)
{
	glfwSetCursorPos(VCWindow::Instance->GLFWWindowHandle, x, y);
}

void VCInteropInputSetCursorVisible(bool val)
{
	if (val)
		glfwSetInputMode(VCWindow::Instance->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	else
		glfwSetInputMode(VCWindow::Instance->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}