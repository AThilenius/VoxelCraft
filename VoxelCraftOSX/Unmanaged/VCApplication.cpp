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

//extern "C"
//{
    void SayHelloUnmanaged()
    {
        cout << "Hello from unmanaged code!" << endl;
    }
//}

void VCApplication::Initialize(int argc, char** argv)
{
    cout << "====================   VoxelCraft Engine Begin   ====================" << endl;
    
	Window = new VCWindow();
    Window->Initalize();

    ObjectStore = new VCObjectStore();
    
    Input = new VCInput();
    Input->Initalize();
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
    
    
    // Test Crap below...
    
    // Test Chunk
    cout << "Creating test chunk..." << endl;
    m_testChunkGO = new VCGameObject();
    m_testChunkGO->SetParent(VCSceneGraph::Instance->RootNode);
    VCChunk* testChunk = new VCChunk(0, 0, 0, NULL);
    
    testChunk->Generate();
    testChunk->StartRebuild();
    testChunk->ContinueRebuild(0.0f);
    
    m_testChunkGO->AttachComponent(testChunk);
    
    
    // MONO TEST
    cout << "===============   Mono - Managed code begin   ===============" << endl;
    m_pRootDomain = mono_jit_init_version("MonoApplication", "v4.0.30319");
    
    // Registry
    VCGameObject::RegisterMonoHandlers();
    VCTransform::RegisterMonoHandlers();
    VCCamera::RegisterMonoHandlers();
    VCInput::RegisterMonoHandlers();
    
    // Assembly
    MonoAssembly *pMonoAssembly = mono_domain_assembly_open(mono_domain_get(), "/Users/Alec/Dropbox/Development/CPP/VoxelCraft/VoxelCraftOSX/Managed/BuildOutput/TestGame.dll");
	m_assemblyImage = mono_assembly_get_image(pMonoAssembly);
    
    // Class
	m_engineType = mono_class_from_name(m_assemblyImage, "VCEngine", "Engine");
	m_engineInstance = mono_object_new(mono_domain_get(), m_engineType);
	
    // Instantiate
    mono_runtime_object_init(m_engineInstance);
    
    // Initalize Method
    MonoMethodDesc* initMethodDesc = mono_method_desc_new ("VCEngine.Engine:Initalize()", true);
    MonoMethod* initMethod = mono_method_desc_search_in_class (initMethodDesc, m_engineType);
    
    // Update Method
    MonoMethodDesc* updateMethodDesc = mono_method_desc_new ("VCEngine.Engine:Update()", true);
    m_updateMethod = mono_method_desc_search_in_class (updateMethodDesc, m_engineType);
    
    // LateUpdate Method
    MonoMethodDesc* lateUpdateMethodDesc = mono_method_desc_new ("VCEngine.Engine:LateUpdate()", true);
    m_lateUpdateMethod = mono_method_desc_search_in_class (lateUpdateMethodDesc, m_engineType);
    
    // Invoke Initalize()
    mono_runtime_invoke(initMethod, m_engineInstance, NULL, NULL);
    
    cout << "===============   Mono - Managed code end     ===============" << endl;
    
    // Resolution Test:
    double startTime = VCTime::CurrentTime();
    while ( startTime == VCTime::CurrentTime() ) {}
    
    cout << "Got a resoltuion of " <<  (VCTime::CurrentTime() - startTime) << endl;
    
}

void VCApplication::Run()
{
    // Disable VSync
    glfwSwapInterval(0);
    
    while(!VCInput::IsKeyDown(GLFW_KEY_ESC))
    {
        Time->Update();
        Input->Update();
        
        mono_runtime_invoke(m_updateMethod, m_engineInstance, NULL, NULL);
        mono_runtime_invoke(m_lateUpdateMethod, m_engineInstance, NULL, NULL);
        
		Renderer->Render();
        SceneGraph->RenderGraph();
        
        // Framerate Check
        double framerate = 1.0f / VCTime::DeltaTime();
        framerate = framerate * 0.05f + m_lastDeltaTime * 0.95f;
        m_lastDeltaTime = framerate;
        stringstream ss;
        ss << "Voxel Craft - " /*<< setprecision(2)*/ << framerate << " FPS.";
        glfwSetWindowTitle( ss.str().c_str() );
        // ~Framerate Check
        
        glfwSwapBuffers();
        glfwPollEvents();
    }
	
    glfwTerminate();
}

