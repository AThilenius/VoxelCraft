//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCWindow.h"

VCWindow* VCWindow::Instance;

VCWindow::VCWindow():
	m_lastDeltaTime(60.0f)
{
	VCWindow::Instance = this;
}

VCWindow::~VCWindow()
{
    
}

static void error_callback(int error, const char* description)
{
    //fputs(description, stderr);
	cout << "GLFW Error Callback: " << description << endl;
}

void VCWindow::Initalize()
{
    cout << "Creating a VCWindow..." << endl;
    
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW." << endl;
		cin.ignore();
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWWindowHandle = glfwCreateWindow(1280, 800, "Voxel Craft", NULL, NULL);
	if (!GLFWWindowHandle)
	{
		glfwTerminate();
		cout << "Failed to create a window." << endl;
		cin.ignore();
	}

	glfwMakeContextCurrent(GLFWWindowHandle);

	glewExperimental = true;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		cin.ignore();
	}

	// ====


	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); 
	glGetIntegerv(GL_MINOR_VERSION, &minor);
    cout << "OpenGL version: " << major << "." << minor << endl;
    cout << "Hardware: " << glGetString(GL_RENDERER) << endl << endl;
    
	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);
	FullViewport = Rectangle(0, 0, Width, Height);

	cout << "VCWindow Initialized." << endl;
    glErrorCheck();
}

void VCWindow::SwapBuffers()
{
	VCTime::Instance->Update();

    // Framerate Check
    float framerate = 1.0f / VCTime::DeltaTime;
    framerate = framerate * 0.05f + m_lastDeltaTime * 0.95f;
    m_lastDeltaTime = framerate;
    stringstream ss;
    ss << "Voxel Craft - " << (int)framerate << " FPS.";
	SetTitle(ss.str());
    // ~Framerate Check

	glfwSwapBuffers(GLFWWindowHandle);
    glfwPollEvents();
}

void VCWindow::SetTitle(string title)
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
	mono_add_internal_call("VCEngine.Window::VCInteropWindowSwapBuffers", (void*)VCInteropWindowSwapBuffers);
	mono_add_internal_call("VCEngine.Window::VCInteropWindowShouldClose", (void*)VCInteropWindowShouldClose);
}

void VCInteropWindowSwapBuffers()
{
	VCWindow::Instance->SwapBuffers();
}

bool VCInteropWindowShouldClose()
{
	return glfwWindowShouldClose(VCWindow::Instance->GLFWWindowHandle);
}
