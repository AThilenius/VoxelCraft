#include "VCApplication.h"

VCApplication::VCApplication(void)
{
}

VCApplication::~VCApplication(void)
{
}

void VCApplication::Initialize()
{
	if (!glfwInit())
		throw exception("Failed to initialize GLFW.");
	
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

	Renderer = new VCGLRenderer();
	Renderer->Initialize();
	
}

void VCApplication::Run()
{
	assert(Renderer, "Call Initialize before calling Run!");

    while (!glfwWindowShouldClose(m_window))
    {
		Renderer->Render();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
	
    glfwTerminate();
}

