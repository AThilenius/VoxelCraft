//
//  SceneGraph.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/23/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCSceneGraph.h"

VCSceneGraph* VCSceneGraph::Instance;

VCSceneGraph::VCSceneGraph()
{
    VCSceneGraph::Instance = this;
    RootNode = new VCGameObject(NULL);
    RootNode->Name = "Root";
}

VCSceneGraph::~VCSceneGraph()
{
}

void VCSceneGraph::Initalize()
{
    cout << "VCSceneGraph Initalized" << endl;
}

void VCSceneGraph::RenderGraph()
{
    if ( m_cameras.size() == 0 )
        cout << "No cameras are registered with the SceneGraph. Please create at least 1 VCCamera." << endl;
    
    FOREACH(iter, m_cameras)
    {
        CurrentRenderingCamera = (*iter);
        CurrentRenderingCamera->PreRender();
        RootNode->Render();
    }
}

void VCSceneGraph::RegisterCamera(VCCamera* camera)
{
    m_cameras.insert(camera);
}

