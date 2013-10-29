//
//  SceneGraph.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/23/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGameObject;
class VCCamera;

#include <unordered_set>
// HACK: Removing causes compiler error
//#include "VCCamera.h"

class VCSceneGraph
{
public:
    VCSceneGraph();
    ~VCSceneGraph();
    
    void Initalize();
    void PrepareSceneGraph();
    
    void RegisterCamera(VCCamera* camera);
    
public:
    static VCSceneGraph* Instance;
    VCCamera* CurrentRenderingCamera;
    VCGameObject* RootNode;
    
private:
    std::unordered_set<VCCamera*> m_cameras;
    
    // ================================      Interop      ============
public:
    static void RegisterMonoHandlers();

private:
    static int s_handle;
    friend int VCInteropGetStaticHandle();

    // ===============================================================
};

// Interop
int VCInteropGetStaticHandle();
