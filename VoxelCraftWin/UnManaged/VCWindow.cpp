//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#define SHOW_GL_WARNINGS 0

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
	
	// Managed event
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

static void glewErrorCallback(int error, const char* description)
{
    //fputs(description, stderr);
	std::cout << "GLFW Error Callback: " << description << std::endl;
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
#if SHOW_GL_WARNINGS
	char debSource[16], debType[20], debSev[5];
	if(source == GL_DEBUG_SOURCE_API_ARB)
		strcpy(debSource, "OpenGL");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
		strcpy(debSource, "Windows");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
		strcpy(debSource, "Shader Compiler");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
		strcpy(debSource, "Third Party");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
		strcpy(debSource, "Application");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
		strcpy(debSource, "Other");

	if(type == GL_DEBUG_TYPE_ERROR_ARB)
		strcpy(debType, "Error");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
		strcpy(debType, "Deprecated behavior");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
		strcpy(debType, "Undefined behavior");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
		strcpy(debType, "Portability");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
		strcpy(debType, "Performance");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)
		strcpy(debType, "Other");

	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
	{
		strcpy(debSev, "High");
		SetConsoleColor(Red);
		printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
			debSource,debType,id,debSev,message);
		std::cin.ignore();
	}

	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
	{
		strcpy(debSev, "Medium");
		SetConsoleColor(Red);
		printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
			debSource,debType,id,debSev,message);
		std::cin.ignore();
	}

	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
	{
		static std::set<std::string> postedWarnings;
		
		strcpy(debSev, "Low");
		std::string post = std::string("Source:") + debSource + "\nType:" + debType + "\nID:" + std::to_string(id) + "\nSeverity:" + debSev + "\nMessage:" + message + "\n";

		if(postedWarnings.find(post) == postedWarnings.end())
		{
			SetConsoleColor(Yellow);
			printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
				debSource,debType,id,debSev,message);

			SetConsoleColor(White);
			postedWarnings.insert(post);
		}
	}

#endif
}

void VCWindow::Initalize()
{
    std::cout << "Creating a VCWindow..." << std::endl;
    
	// =====   GLFW   ======================================================
	glfwSetErrorCallback(glewErrorCallback);

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << std::endl;
		std::cin.ignore();
	}
	 
	//glfwWindowHint(GLFW_DECORATED, false);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	GLFWWindowHandle = glfwCreateWindow(1280, 600, "Thilenius - A 0.0.1", NULL, NULL);
	if (!GLFWWindowHandle)
	{
		glfwTerminate();
		std::cout << "Failed to create a window." << std::endl;
		std::cin.ignore();
	}

	glfwMakeContextCurrent(GLFWWindowHandle);

	// =====   GLEW   ======================================================
	glewExperimental = true;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		std::cin.ignore();
	}

	// =====   Debug   ======================================================
#if DEBUG
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glDebugCallback, NULL);
#endif


	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); 
	glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout << "OpenGL version: " << major << "." << minor << std::endl;
    std::cout << "Hardware: " << glGetString(GL_RENDERER) << std::endl << std::endl;
    
	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);
	FullViewport = VCRectangle(0, 0, Width, Height);

	//SizeChangeFunction = VCMonoRuntime::GetMonoMethod("Window", "GlfwSizeChangeHandler(int,int)");
	//glfwSetFramebufferSizeCallback(GLFWWindowHandle, _glfwFramebuferSizeCallback);


	SetVSync(false);
	std::cout << "VCWindow Initialized." << std::endl;
    glErrorCheck();

	VCInteropWindowSetPos(200, 200);
}

void VCWindow::SwapBuffers()
{
	VCTime::Instance->Update();

	glfwSwapBuffers(GLFWWindowHandle);
}

void VCWindow::PollEvents()
{
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
	VCMonoRuntime::SetMethod("Window::VCInteropWindowSwapBuffers",	(void*)VCInteropWindowSwapBuffers);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowPollEvents",	(void*)VCInteropWindowPollEvents);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowShouldClose",	(void*)VCInteropWindowShouldClose);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowGetSize",		(void*)VCInteropWindowGetSize);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowSetSize",		(void*)VCInteropWindowSetSize);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowGetPos",		(void*)VCInteropWindowGetPos);
	VCMonoRuntime::SetMethod("Window::VCInteropWindowSetPos",		(void*)VCInteropWindowSetPos);
	VCMonoRuntime::SetMethod("Window::VCInteropGetMonitorSize",		(void*)VCInteropGetMonitorSize);
}

void VCInteropWindowSwapBuffers()
{
	VCWindow::Instance->SwapBuffers();
}

void VCInteropWindowPollEvents()
{
	VCWindow::Instance->PollEvents();
}

bool VCInteropWindowShouldClose()
{
	return glfwWindowShouldClose(VCWindow::Instance->GLFWWindowHandle);
}

void VCInteropWindowGetSize(int* width, int* height)
{
	glfwGetWindowSize(VCWindow::Instance->GLFWWindowHandle, width, height);
}

void VCInteropWindowSetSize( int width, int height )
{
	glfwSetWindowSize(VCWindow::Instance->GLFWWindowHandle, width, height);
	VCWindow::Instance->Height = height;
	VCWindow::Instance->Width = width;
	VCWindow::Instance->FullViewport = VCRectangle(0, 0, width, height);
}

void VCInteropWindowGetPos( int* x, int* y )
{
	glfwGetWindowPos(VCWindow::Instance->GLFWWindowHandle, x, y);
}

void VCInteropWindowSetPos( int x, int y )
{
	glfwSetWindowPos(VCWindow::Instance->GLFWWindowHandle, x, y);
}

void VCInteropGetMonitorSize( int* width, int* height )
{
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	*width = mode->width;
	*height = mode->height;
}
