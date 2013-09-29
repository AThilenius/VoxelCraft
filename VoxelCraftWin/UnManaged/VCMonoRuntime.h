//
//  VCMonoBinder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCMonoBinder__
#define __VoxelCraftOSX__VCMonoBinder__

#include "PCH.h"

#include "VCCamera.h"
#include "VCGameObject.h"
#include "VCPhysics.h"

class VCMonoRuntime
{
public:
    VCMonoRuntime();
    ~VCMonoRuntime();
    
    void Initalize();
    
    void InvokeInitalize();
    void InvokeStart();
    void InvokeUpdate();
    void InvokeLateUpdate();
    void InvokePreRender();
    
private:
    void Bind();
    
private:
    MonoDomain *m_pRootDomain;
	MonoImage *m_assemblyImage;
    
	MonoClass *m_engineType;
	MonoObject *m_engineInstance;
    
    MonoMethod* m_initMethod;
    MonoMethod* m_startMethod;
    MonoMethod* m_updateMethod;
    MonoMethod* m_lateUpdateMethod;
    MonoMethod* m_preRenderMethod;
};

#endif /* defined(__VoxelCraftOSX__VCMonoBinder__) */
