//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCInput.h"
#include "VCGLWindow.h"


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
	glfwSetCursorPos(VCGLWindow::ActiveWindow->GLFWWindow, x, y);
}

void VCInteropInputSetCursorVisible(bool val)
{
	//if (val)
	//	glfwSetInputMode(VCGLWindow::ActiveWindow->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//else
	//	glfwSetInputMode(VCGLWindow::ActiveWindow->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

DLL_EXPORT_API void VCInteropInputSetCallbacks( GlfwKeyCallback keyCallback, 
											   GlfwCharCallback charCallback, 
											   GlfwMouseMoveCallback mouseMoveCallback, 
											   GlfwMouseClickCallback mouseClickCallback, 
											   GlfwMouseEnterCallback mouseEnterCallback, 
											   GlfwMouseScrollCallback mouseScrollCallback )
{
	//GlfwKeyCallbackDelegate = keyCallback;
	//GlfwCharCallbackDelegate = charCallback;
	//GlfwMouseMoveCallbackDelegate = mouseMoveCallback;
	//GlfwMouseClickCallbackDelegate = mouseClickCallback;
	//GlfwMouseEnterCallbackDelegate = mouseEnterCallback;
	//GlfwMouseScrollCallbackDelegate = mouseScrollCallback;


	//glfwSetScrollCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwMouseScrollCallback);
	//glfwSetCursorEnterCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwMouseEnterCallback);
	//glfwSetMouseButtonCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwMouseClickCallback);
	//glfwSetCursorPosCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwMouseMoveCallback);
	//glfwSetCharCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwCharCallback);
	//glfwSetKeyCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, &_GlfwKeyCallback);

	//// Set initial mouse position
	//double x, y;
	//glfwGetCursorPos(VCGLWindow::ActiveWindow->GLFWWindowHandle, &x, &y);
	//_GlfwMouseMoveCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, x, y);
}
