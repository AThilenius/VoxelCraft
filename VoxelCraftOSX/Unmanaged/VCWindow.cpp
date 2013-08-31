//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCWindow.h"

VCWindow::VCWindow()
{
    
}

VCWindow::~VCWindow()
{
    
}

void VCWindow::Initalize()
{
    cout << "Creating a VCWindow..." << endl;
    
    if (!glfwInit())
		cout << "Failed to initialize GLFW." << endl;
    
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 6,6,6,6, 24,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
    }
    
    // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }
    
    glfwSetWindowTitle( "Voxel Craft" );
    
    int major, minor, rev = 0;
    glfwGetGLVersion(&major, &minor, &rev);
    cout << "OpenGL version recieved: " << major << "." << minor << "." << rev << endl;
    cout << "Hardware: " << glGetString(GL_RENDERER) << endl << endl;
    
    glErrorCheck();
}