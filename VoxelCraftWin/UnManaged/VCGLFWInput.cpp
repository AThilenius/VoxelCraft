//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLFWInput.h"
#include "VCGLWindow.h"
#include "VCObjectStore.h"


GlfwKeyCallback GlfwKeyCallbackDelegate = 0;
GlfwCharCallback GlfwCharCallbackDelegate = 0;
GlfwMouseMoveCallback GlfwMouseMoveCallbackDelegate = 0;
GlfwMouseClickCallback GlfwMouseClickCallbackDelegate = 0;
GlfwMouseEnterCallback GlfwMouseEnterCallbackDelegate = 0;
GlfwMouseScrollCallback GlfwMouseScrollCallbackDelegate = 0;

void _GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(GlfwKeyCallbackDelegate)
		GlfwKeyCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, key, scancode, action, mods);
}

void _GlfwCharCallback(GLFWwindow* window, unsigned int charCode)
{
	if(GlfwCharCallbackDelegate)
		GlfwCharCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, charCode);
}

void _GlfwMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	if(GlfwMouseMoveCallbackDelegate)
		GlfwMouseMoveCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, x, y);
}

void _GlfwMouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if(GlfwMouseClickCallbackDelegate)
		GlfwMouseClickCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, button, action, mods);
}

void _GlfwMouseEnterCallback(GLFWwindow* window, int entered)
{
	if(GlfwMouseEnterCallbackDelegate)
		GlfwMouseEnterCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, entered);
}

void _GlfwMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if(GlfwMouseScrollCallbackDelegate)
		GlfwMouseScrollCallbackDelegate(VCGLWindow::GetWindowFromGLFW(window)->Handle, xOffset, yOffset);
}


VCGLFWInput::VCGLFWInput(VCGLWindow* window)
{
	glfwSetScrollCallback(window->GLFWWindowHandle, &_GlfwMouseScrollCallback);
	glfwSetCursorEnterCallback(window->GLFWWindowHandle, &_GlfwMouseEnterCallback);
	glfwSetMouseButtonCallback(window->GLFWWindowHandle, &_GlfwMouseClickCallback);
	glfwSetCursorPosCallback(window->GLFWWindowHandle, &_GlfwMouseMoveCallback);
	glfwSetCharCallback(window->GLFWWindowHandle, &_GlfwCharCallback);
	glfwSetKeyCallback(window->GLFWWindowHandle, &_GlfwKeyCallback);

	// Set initial mouse position
	double x, y;
	glfwGetCursorPos(window->GLFWWindowHandle, &x, &y);
	_GlfwMouseMoveCallback(window->GLFWWindowHandle, x, y);
}

VCGLFWInput::~VCGLFWInput()
{
    
}

void VCInteropInputSetMouse(int windowHandle, float x, float y)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(windowHandle);
	glfwSetCursorPos(obj->GLFWWindowHandle, x, y);
}

void VCInteropInputSetCursorVisible(int windowHandle, bool val)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(windowHandle);

	if (val)
		glfwSetInputMode(obj->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	else
		glfwSetInputMode(obj->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void VCInteropInputSetCallbacks( GlfwKeyCallback keyCallback, 
											   GlfwCharCallback charCallback, 
											   GlfwMouseMoveCallback mouseMoveCallback, 
											   GlfwMouseClickCallback mouseClickCallback, 
											   GlfwMouseEnterCallback mouseEnterCallback, 
											   GlfwMouseScrollCallback mouseScrollCallback )
{
	GlfwKeyCallbackDelegate = keyCallback;
	GlfwCharCallbackDelegate = charCallback;
	GlfwMouseMoveCallbackDelegate = mouseMoveCallback;
	GlfwMouseClickCallbackDelegate = mouseClickCallback;
	GlfwMouseEnterCallbackDelegate = mouseEnterCallback;
	GlfwMouseScrollCallbackDelegate = mouseScrollCallback;
}
