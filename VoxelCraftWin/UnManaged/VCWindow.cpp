//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCWindow.h"

#include "VCMonoMethod.h"
#include "VCMonoRuntime.h"
#include "VCTime.h"

VCWindow* VCWindow::Instance;

void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height)
{
	VCWindow::Instance->Width = width;
	VCWindow::Instance->Height = height;
	VCWindow::Instance->FullViewport = VCRectangle(0, 0, width, height);

	void* args[2] = { &width, &height };
	VCWindow::Instance->SizeChangeFunction->Invoke(args);
	glViewport(0, 0, width, height);
}

VCWindow::VCWindow()
{
	VCWindow::Instance = this;
}

VCWindow::~VCWindow()
{
    
}

static void error_callback(int error, const char* description)
{
    //fputs(description, stderr);
	std::cout << "GLFW Error Callback: " << description << std::endl;
}

void VCWindow::Initalize()
{
    std::cout << "Creating a VCWindow..." << std::endl;
    
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << std::endl;
		std::cin.ignore();
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWWindowHandle = glfwCreateWindow(1280, 600, "VoxelEngine 0.2.1 - Thilenius", NULL, NULL);
	if (!GLFWWindowHandle)
	{
		glfwTerminate();
		std::cout << "Failed to create a window." << std::endl;
		std::cin.ignore();
	}

	glfwMakeContextCurrent(GLFWWindowHandle);

	glewExperimental = true;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		std::cin.ignore();
	}

	// ====


	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); 
	glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout << "OpenGL version: " << major << "." << minor << std::endl;
    std::cout << "Hardware: " << glGetString(GL_RENDERER) << std::endl << std::endl;
    
	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);
	FullViewport = VCRectangle(0, 0, Width, Height);

	SizeChangeFunction = VCMonoRuntime::GetMonoMethod("Window", "GlfwSizeChangeHandler(int,int)");
	glfwSetFramebufferSizeCallback(GLFWWindowHandle, _glfwFramebuferSizeCallback);

	SetVSync(false);
	std::cout << "VCWindow Initialized." << std::endl;
    glErrorCheck();
}

void VCWindow::SwapBuffers()
{
	VCTime::Instance->Update();

	glfwSwapBuffers(GLFWWindowHandle);
    glfwPollEvents();
}

void VCWindow::SetTitle(std::string title)
{
	glfwSetWindowTitle(GLFWWindowHandle, title.c_str());
}

void VCWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	
	else
		glfwSwapInterval(0);
}

void VCWindow::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Window::VCInteropWindowSwapBuffers",	(void*)VCInteropWindowSwapBuffers);
	mono_add_internal_call("VCEngine.Window::VCInteropWindowShouldClose",	(void*)VCInteropWindowShouldClose);
	mono_add_internal_call("VCEngine.Window::VCInteropWindowGetSize",		(void*)VCInteropWindowGetSize);
}

void VCInteropWindowSwapBuffers()
{
	VCWindow::Instance->SwapBuffers();
}

bool VCInteropWindowShouldClose()
{
	return glfwWindowShouldClose(VCWindow::Instance->GLFWWindowHandle);
}

void VCInteropWindowGetSize(int* width, int* height)
{
	//return Point(VCWindow::Instance->Width, VCWindow::Instance->Height);
	*width = 1280;
	*height = 600;
}
