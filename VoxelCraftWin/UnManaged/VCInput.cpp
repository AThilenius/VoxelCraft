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


GlfwKeyCallback GlfwKeyCallbackDelegate = 0;
GlfwCharCallback GlfwCharCallbackDelegate = 0;
GlfwMouseMoveCallback GlfwMouseMoveCallbackDelegate = 0;
GlfwMouseClickCallback GlfwMouseClickCallbackDelegate = 0;
GlfwMouseEnterCallback GlfwMouseEnterCallbackDelegate = 0;
GlfwMouseScrollCallback GlfwMouseScrollCallbackDelegate = 0;

void _GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GlfwKeyCallbackDelegate(key, scancode, action, mods);
}

void _GlfwCharCallback(GLFWwindow* window, unsigned int charCode)
{
	GlfwCharCallbackDelegate(charCode);
}

void _GlfwMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	GlfwMouseMoveCallbackDelegate(x, y);
}

void _GlfwMouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	GlfwMouseClickCallbackDelegate(button, action, mods);
}

void _GlfwMouseEnterCallback(GLFWwindow* window, int entered)
{
	GlfwMouseEnterCallbackDelegate(entered);
}

void _GlfwMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	GlfwMouseScrollCallbackDelegate(xOffset, yOffset);
}


VCInput::VCInput()
{
}

VCInput::~VCInput()
{
    
}

void VCInput::Initalize()
{
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

DLL_EXPORT_API void VCInteropInputSetCallbacks( GlfwKeyCallback keyCallback, 
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
