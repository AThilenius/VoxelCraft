//
//  VCInputPreProcessor.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCInput.h"
#include "VCWindow.h"

VCInput::VCInput()
{
}

VCInput::~VCInput()
{
    
}

void VCInput::Initalize()
{
}

// ================================      Interop      ============
void VCInput::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Input::VCInteropInputGetMouse",			(void*)VCInteropInputGetMouse);
    mono_add_internal_call("VCEngine.Input::VCInteropInputSetMouse",			(void*)VCInteropInputSetMouse);
	mono_add_internal_call("VCEngine.Input::VCInteropInputGetKey",				(void*)VCInteropInputGetKey);
	mono_add_internal_call("VCEngine.Input::VCInteropInputSetCursorVisible",    (void*)VCInteropInputSetCursorVisible);
}

void VCInteropInputGetMouse(float* x, float* y, bool* left, bool* right)
{
	double dx, dy;
	glfwGetCursorPos(VCWindow::Instance->GLFWWindowHandle, &dx, &dy);
	*x = dx;
	*y = dy;
	*left = glfwGetMouseButton(VCWindow::Instance->GLFWWindowHandle, 0);
	*right = glfwGetMouseButton(VCWindow::Instance->GLFWWindowHandle, 1);
}

void VCInteropInputSetMouse(float x, float y)
{
	glfwSetCursorPos(VCWindow::Instance->GLFWWindowHandle, x, y);
}

bool VCInteropInputGetKey(int key)
{
	return glfwGetKey(VCWindow::Instance->GLFWWindowHandle, key);
}

void VCInteropInputSetCursorVisible(bool val)
{
	if (val)
		glfwSetInputMode(VCWindow::Instance->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	else
		glfwSetInputMode(VCWindow::Instance->GLFWWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
