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
    cout << "====================   VoxelCraft Engine Begin   ====================" << endl;
    
	Window = new VCWindow();
    Window->Initalize();

    
    Input = new VCInput();
    Input->Initalize();
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
    
    
    // Test Crap below...
    
    // Camera
    cout << "Creating Camera..." << endl;
    VCGameObject* cameraObject = new VCGameObject();
    VCCamera* mainCamera = new VCCamera();
    cameraObject->AttachComponent(mainCamera);
    cameraObject->Transform->Position = vec3(50, -25, -120);
    cameraObject->Transform->Rotate(vec3(0, 0.7f, 0));

    // Test Chunk
    cout << "Creating test chunk..." << endl;
    m_testChunkGO = new VCGameObject();
    VCChunk* testChunk = new VCChunk(0, 0, 0, NULL);
    
    testChunk->Generate();
    testChunk->StartRebuild();
    testChunk->ContinueRebuild(0.0f);
    
    m_testChunkGO->AttachComponent(testChunk);
    
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

void VCApplication::Run()
{   
    //while (!glfwWindowShouldClose(m_window))
    while(!VCInput::IsKeyDown(GLFW_KEY_ESC))
    {
        Time->Update();
        Input->Update();
		Renderer->Render();
        //m_testChunk->Render();
        SceneGraph->RenderGraph();
        
        // Framerate Check
        double framerate = 1.0f / VCTime::DeltaTime();
        framerate = framerate * 0.05f + m_lastDeltaTime * 0.95f;
        m_lastDeltaTime = framerate;
        stringstream ss;
        ss << "Voxel Craft - " << setprecision(2) << framerate << " FPS.";
        glfwSetWindowTitle( ss.str().c_str() );
        // ~Framerate Check
        
        glfwSwapBuffers();
        glfwPollEvents();
    }
	
    glfwTerminate();
}

