//
//  SceneGraph.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/23/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__SceneGraph__
#define __VoxelCraftOSX__SceneGraph__

#import "PCH.h"
#import "VCGameObject.h"

class VCSceneGraph
{
public:
    VCSceneGraph();
    ~VCSceneGraph();
    
    void Initalize();
    void RenderGraph();
    
public:
    static VCSceneGraph* Instance;
    VCGameObject* RootNode;
};

#endif /* defined(__VoxelCraftOSX__SceneGraph__) */
