//
//  SceneGraph.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/23/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCSceneGraph.h"

#include "VCGameObject.h"
#include "VCCamera.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"

VCSceneGraph* VCSceneGraph::Instance;
int VCSceneGraph::s_handle;

VCSceneGraph::VCSceneGraph()
{
    VCSceneGraph::Instance = this;
}

VCSceneGraph::~VCSceneGraph()
{
}

void VCSceneGraph::Initalize()
{
	VCSceneGraph::s_handle = VCObjectStore::Instance->RegisterObject(this);
	RootNode = new VCGameObject();
	RootNode->Name = "Root";
    std::cout << "VCSceneGraph Initialized" << std::endl;
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

	RootNode->PreRender();
}

// ================================      Interop      ============
void VCSceneGraph::RegisterMonoHandlers()
{
    VCMonoRuntime::SetMethod("SceneGraph::VCInteropGetStaticHandle", (void*) VCInteropGetStaticHandle);
}

int VCInteropGetStaticHandle()
{
    return VCSceneGraph::s_handle;
}

