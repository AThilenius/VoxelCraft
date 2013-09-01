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

void VCApplication::Initialize(int argc, char** argv)
{
    cout << "====================   VoxelCraft Engine Begin   ====================" << endl;
    
	Window = new VCWindow();
    Window->Initalize();

    ObjectStore = new VCObjectStore();
    ObjectStore->Initalize();
    
    Input = new VCInput();
    Input->Initalize();
    
	Renderer = new VCGLRenderer();
	Renderer->Initialize();
    
    Time = new VCTime();
    Time->Initalize();
    
    SceneGraph = new VCSceneGraph();
    SceneGraph->Initalize();
    
    MonoRuntime = new VCMonoRuntime();
    MonoRuntime->Initalize();
    MonoRuntime->InvokeInitalize();
    
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
}

void VCApplication::Run()
{
    // Disable VSync
    glfwSwapInterval(0);
    
    while(!VCInput::IsKeyDown(GLFW_KEY_ESC))
    {
        Time->Update();
        Input->Update();
        
        MonoRuntime->InvokeUpdate();
        MonoRuntime->InvokeLateUpdate();
        
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

