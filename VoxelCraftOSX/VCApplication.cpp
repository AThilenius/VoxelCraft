//
//  VCApplication.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCApplication.h"

VCApplication* VCApplication::Instance;

VCApplication::VCApplication(void)
{
    VCApplication::Instance = this;
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
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
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
    cout << "OpenGL version recieved: " << major << "." << minor << "." << rev << endl << endl;
    
    glErrorCheck();

	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Input = new VCInput();
    Input->Initalize();
    
    Time = new VCTime();
    Time->Initalize();
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glErrorCheck();
    
    m_testChunk = new VCChunk(0, 0, 0, NULL);
    m_testChunk->Generate();
    m_testChunk->StartRebuild();
    m_testChunk->ContinueRebuild(0.0f);
    
    // MONO TEST
    cout << "===============   Mono - Managed code begin   ===============" << endl;
    m_pRootDomain = mono_jit_init_version("MonoApplication", "v4.0.30319");
    
    MonoAssembly *pMonoAssembly = mono_domain_assembly_open(mono_domain_get(), "/Users/Alec/ClassLibrary.dll");
	m_pClassLibraryImage = mono_assembly_get_image(pMonoAssembly);
    
	m_pClassLibraryManagerClass = mono_class_from_name(m_pClassLibraryImage, "ClassLibraryNamespace", "ClassLibraryManager");
    
	m_pClassLibraryManager = mono_object_new(mono_domain_get(), m_pClassLibraryManagerClass);
	mono_runtime_object_init(m_pClassLibraryManager);
    cout << "===============   Mono - Managed code end     ===============" << endl;
}

struct testStruct
{
    float f1, f2, f3, f4, f5, f6;
};

void VCApplication::Run()
{
    vector<testStruct> testList;
    testStruct t1;
    t1.f1 = 42.0f;
    testList.push_back(t1);
    
    cout << "Val: " << testList[0].f1 << endl;
    
    
    //while (!glfwWindowShouldClose(m_window))
    while(!VCInput::IsKeyDown(GLFW_KEY_ESC))
    {
		Renderer->Render();
        Time->Update();
        m_testChunk->Render();
        
        glfwSwapBuffers();
        glfwPollEvents();
    }
	
    glfwTerminate();
}

