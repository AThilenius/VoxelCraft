//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCWindow.h"

VCWindow* VCWindow::Instance;

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
	cout << "GLFW Error Callback: " << description << endl;
}

void VCWindow::Initalize()
{
    cout << "Creating a VCWindow..." << endl;
    
	glfwSetErrorCallback(error_callback);

    if (!glfwInit())
		cout << "Failed to initialize GLFW." << endl;
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Core needed?

	GLFWwindow* window = glfwCreateWindow(640, 480, "Voxel Craft", NULL, NULL);

	if(!window)
	{
		fprintf(stderr, "Failed to create a GLFW window!\n");
		glfwTerminate();
	}

    // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }
    
    //int major, minor, rev = 0;
    //glfwGetGLVersion(&major, &minor, &rev);
    //cout << "OpenGL version recieved: " << major << "." << minor << "." << rev << endl;
    cout << "Hardware: " << glGetString(GL_RENDERER) << endl << endl;
    
	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);

    glErrorCheck();
}

void VCWindow::SwapBuffers()
{
	glfwSwapBuffers(GLFWWindowHandle);
    glfwPollEvents();
}

void VCWindow::SetTitle(string title)
{
	glfwSetWindowTitle(GLFWWindowHandle, title.c_str());
}