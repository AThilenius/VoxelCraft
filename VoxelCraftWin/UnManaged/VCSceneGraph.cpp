//
//  SceneGraph.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/23/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCSceneGraph.h"

VCSceneGraph* VCSceneGraph::Instance;
int VCSceneGraph::s_handle;

VCSceneGraph::VCSceneGraph()
{
    VCSceneGraph::Instance = this;
    VCSceneGraph::s_handle = VCObjectStore::Instance->RegisterObject(this);
    RootNode = new VCGameObject();
    RootNode->Name = "Root";
}

VCSceneGraph::~VCSceneGraph()
{
}

void VCSceneGraph::Initalize()
{
    std::cout << "VCSceneGraph Initalized" << std::endl;
}

void VCSceneGraph::PrepareSceneGraph()
{
    //if ( m_cameras.size() == 0 )
    //    std::cout << "No cameras are registered with the SceneGraph. Please create at least 1 VCCamera." << std::endl;
    //
    //FOREACH(iter, m_cameras)
    //{
    //    CurrentRenderingCamera = (*iter);
    //    CurrentRenderingCamera->PreRender();
    //    RootNode->Render();
    //}

	// HACK
	CurrentRenderingCamera->PreRender();

	RootNode->PreRender();
}

void VCSceneGraph::RegisterCamera(VCCamera* camera)
{
	m_cameras.insert(camera);

	// HACK
	CurrentRenderingCamera = camera;
}

// ================================      Interop      ============
void VCSceneGraph::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.SceneGraph::VCInteropGetStaticHandle", (void*) VCInteropGetStaticHandle);
}

int VCInteropGetStaticHandle()
{
    return VCSceneGraph::s_handle;
}

