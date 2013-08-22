//
//  VCTestApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTestApplication.h"

VCTestApplication::VCTestApplication()
{
    
}

VCTestApplication::~VCTestApplication()
{
    
}

void VCTestApplication::Initialize()
{
	if (!glfwInit())
		cout << "Failed to initialize GLFW." << endl;

#ifdef __APPLE__
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
    }
    
    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }
    
    glfwSetWindowTitle( "Tutorial 01" );
    
    int major, minor, rev = 0;
    glfwGetGLVersion(&major, &minor, &rev);
    cout << "OpenGL version recieved: " << major << "." << minor << "." << rev << endl << endl;
#else
	m_window = glfwCreateWindow(640, 480, "Voxel Craft", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		throw exception("Failed to create a window.");
	}

	glfwMakeContextCurrent(m_window);

	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		throw new exception ( "Failed to init GLEW." );
	}
#endif
    
    glErrorCheck();
    
    m_testShader = new VCTestShader();
    m_testShader->Initialize();
    m_testShader->Bind();
}

void VCTestApplication::Run()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glErrorCheck();
    
    m_bufferId = 0;
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);

	ZERO_CHECK(m_bufferId);
    
    cout << "Got buffer ID: " << m_bufferId << endl;

    GLfloat m_verts[9] =
    {
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, -1.0f,
        1.0f, 0.0f, -1.0f
    };
    
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, &(m_verts[0]) , GL_STATIC_DRAW);
    glErrorCheck();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glErrorCheck();
    
    
    
    
    // Draw test triangle
    glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_testShader->Bind();
    glErrorCheck();
    
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glErrorCheck();
    
    glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
    glErrorCheck();
    
    glVertexAttribPointer(VC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0 );
    glErrorCheck();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glErrorCheck();
    
    // Release
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glErrorCheck();
    
    glDisableVertexAttribArray(VC_ATTRIBUTE_POSITION);
    glErrorCheck();
    
#ifdef __APPLE__
    glfwSwapBuffers();
#else
	glfwSwapBuffers(m_window);
#endif

    glfwPollEvents();
    
    
    //while (!glfwWindowShouldClose(m_window))
    while(true)
    {
		//Renderer->Render();
        //glfwSwapBuffers(m_window);
        
        
        
        
        //glfwSwapBuffers();
        //glfwPollEvents();
    }
	
    glfwTerminate();
}