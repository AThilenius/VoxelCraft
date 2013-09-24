//
//  VCUpdateManager.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCUpdateManager.h"

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
        cout << "Please invoke Engine.Initalize()" << endl;
    
    (*staticCallback)();
}


// ================================      Interop      ===========
void VCUpdateManager::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.VCEngineCore::VCInteropRegisterUpdateHandler", (void*)VCInteropRegisterUpdateHandler);
}

void VCInteropRegisterUpdateHandler(noArgCallback* callback)
{
    staticCallback = callback;
    
    cout << "Test calling Callback" << endl;
    (*staticCallback)();
}