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
		cout << "Failed to initialize GLFW." << endl;
    
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
	if ( glfwOpenWindow(640, 400, 8, 8, 8, 8, 8, 0, GLFW_WINDOW) != GL_TRUE )
	{
        cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
	}

    glfwSetWindowTitle("Voxel Craft OS X");
    
    int major, minor, rev = 0;
    glfwGetGLVersion(&major, &minor, &rev);
    cout << "OpenGL version recieved: " << major << "." << minor << "." << rev << endl;
    
//#ifndef __APPLE__
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
		cout << "Error initializing GLEW! " << glewGetErrorString( glewError ) << endl;
    
//#endif
    
    glErrorCheck();

	Renderer = new VCGLRenderer();
	Renderer->Initialize();
}

void VCApplication::Run()
{
	//assert(Renderer, "Call Initialize before calling Run!");

    //while (!glfwWindowShouldClose(m_window))
    while(true)
    {
		Renderer->Render();
        //glfwSwapBuffers(m_window);
        glfwSwapBuffers();
        glfwPollEvents();
    }
	
    glfwTerminate();
}

