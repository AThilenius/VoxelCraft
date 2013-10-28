//
//  VCUpdateManager.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCUpdateManager.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"

VCUpdateManager* VCUpdateManager::Instance;
static noArgCallback* staticCallback;

VCUpdateManager::VCUpdateManager()
{
    Handle = VCObjectStore::Instance->RegisterObject(this);
    VCUpdateManager::Instance = this;
    staticCallback = NULL;
}

VCUpdateManager::~VCUpdateManager()
{
    VCObjectStore::Instance->ReleaseObject(Handle);
}

void VCUpdateManager::Update()
{
    if (!staticCallback)
        std::cout << "Please invoke Engine.Initalize()" << std::endl;
    
    (*staticCallback)();
}


// ================================      Interop      ===========
void VCUpdateManager::RegisterMonoHandlers()
{
    VCMonoRuntime::SetMethod("VCEngineCore::VCInteropRegisterUpdateHandler", (void*)VCInteropRegisterUpdateHandler);
}

void VCInteropRegisterUpdateHandler(noArgCallback* callback)
{
    staticCallback = callback;
    
    std::cout << "Test calling Callback" << std::endl;
    (*staticCallback)();
}