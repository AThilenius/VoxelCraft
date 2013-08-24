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
    
}

void VCSceneGraph::RenderGraph()
{
    RootNode->Render();
}