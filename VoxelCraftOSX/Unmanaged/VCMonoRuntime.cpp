//
//  VCMonoBinder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCMonoRuntime.h"

VCMonoRuntime::VCMonoRuntime()
{
    
}

VCMonoRuntime::~VCMonoRuntime()
{
    
}

void VCMonoRuntime::Initalize()
{
    cout << "===============   Mono - Managed code begin   ===============" << endl;
    m_pRootDomain = mono_jit_init_version("MonoApplication", "v4.0.30319");
    
    // Setup Bindings
    Bind();
    
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
    m_initMethod = mono_method_desc_search_in_class (initMethodDesc, m_engineType);
    
    // Update Method
    MonoMethodDesc* updateMethodDesc = mono_method_desc_new ("VCEngine.Engine:Update()", true);
    m_updateMethod = mono_method_desc_search_in_class (updateMethodDesc, m_engineType);
    
    // LateUpdate Method
    MonoMethodDesc* lateUpdateMethodDesc = mono_method_desc_new ("VCEngine.Engine:LateUpdate()", true);
    m_lateUpdateMethod = mono_method_desc_search_in_class (lateUpdateMethodDesc, m_engineType);
    
    cout << "===============   Mono - Managed code end     ===============" << endl;
}

void VCMonoRuntime::Bind()
{
    // Registry
    VCGameObject::RegisterMonoHandlers();
    VCTransform::RegisterMonoHandlers();
    VCCamera::RegisterMonoHandlers();
    VCInput::RegisterMonoHandlers();
}

void VCMonoRuntime::InvokeInitalize()
{
    mono_runtime_invoke(m_initMethod, m_engineInstance, NULL, NULL);
}

void VCMonoRuntime::InvokeUpdate()
{
    mono_runtime_invoke(m_updateMethod, m_engineInstance, NULL, NULL);
}

void VCMonoRuntime::InvokeLateUpdate()
{
    mono_runtime_invoke(m_lateUpdateMethod, m_engineInstance, NULL, NULL);
}