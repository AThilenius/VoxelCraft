//
//  VCMonoBinder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCMonoBinder__
#define __VoxelCraftOSX__VCMonoBinder__

#import "PCH.h"
#import "VCCamera.h"
#import "VCGameObject.h"

class VCMonoRuntime
{
public:
    VCMonoRuntime();
    ~VCMonoRuntime();
    
    void Initalize();
    
    void InvokeInitalize();
    void InvokeUpdate();
    void InvokeLateUpdate();
    
private:
    void Bind();
    
private:
    MonoDomain *m_pRootDomain;
	MonoImage *m_assemblyImage;
    
	MonoClass *m_engineType;
	MonoObject *m_engineInstance;
    
    MonoMethod* m_initMethod;
    MonoMethod* m_updateMethod;
    MonoMethod* m_lateUpdateMethod;
};

#endif /* defined(__VoxelCraftOSX__VCMonoBinder__) */
