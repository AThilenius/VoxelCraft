//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCInput.h"
#include "VCWindow.h"
#include "VCMonoRuntime.h"

VCMonoMethod* VCInput::MouseScrollCallback;
VCMonoMethod* VCInput::MouseEnterCallback;
VCMonoMethod* VCInput::MouseClickCallback;
VCMonoMethod* VCInput::MouseMoveCallback;
VCMonoMethod* VCInput::KeyCallback;

void _GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	void* args[4] = { &key, &scancode, &action, &mods };
	VCInput::KeyCallback->Invoke(args);
}

void _GlfwMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	void* args[2] = { &x, &y };
	VCInput::MouseMoveCallback->Invoke(args);
}

void _GlfwMouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	void* args[3] = { &button, &action, &mods };
	VCInput::MouseClickCallback->Invoke(args);
}

void _GlfwMouseEnterCallback(GLFWwindow* window, int entered)
{
	void* args[1] = { &entered };
	VCInput::MouseEnterCallback->Invoke(args);
}

void _GlfwMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	void* args[2] = { &xOffset, &yOffset };
	VCInput::MouseScrollCallback->Invoke(args);
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
	VCInput::MouseScrollCallback = VCMonoRuntime::GetMonoMethod("Input", "GlfwMouseScrollCallback(double,double)");
	VCInput::MouseEnterCallback = VCMonoRuntime::GetMonoMethod("Input", "GlfwMouseEnterCallback(int)");
	VCInput::MouseClickCallback = VCMonoRuntime::GetMonoMethod("Input", "GlfwMouseClickCallback(int,int,int)");
	VCInput::MouseMoveCallback = VCMonoRuntime::GetMonoMethod("Input", "GlfwMouseMoveCallback(double,double)");
	VCInput::KeyCallback = VCMonoRuntime::GetMonoMethod("Input", "GlfwKeyCallback(int,int,int,int)");

	glfwSetScrollCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseScrollCallback);
	glfwSetCursorEnterCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseEnterCallback);
	glfwSetMouseButtonCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseClickCallback);
	glfwSetCursorPosCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwMouseMoveCallback);
	glfwSetKeyCallback(VCWindow::Instance->GLFWWindowHandle, &_GlfwKeyCallback);
}

// ================================      Interop      ============
void VCInput::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Input::VCInteropInputGetMouse",			(void*)VCInteropInputGetMouse);
    mono_add_internal_call("VCEngine.Input::VCInteropInputSetMouse",			(void*)VCInteropInputSetMouse);
	mono_add_internal_call("VCEngine.Input::VCInteropInputSetCursorVisible",    (void*)VCInteropInputSetCursorVisible);
}

void VCInteropInputGetMouse(float* x, float* y)
{
	double dx, dy;
	glfwGetCursorPos(VCWindow::Instance->GLFWWindowHandle, &dx, &dy);
	*x = dx;
	*y = dy;
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