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
		VCLog::Info("Please invoke Engine.Initalize()", "Initialize");
    
    (*staticCallback)();
}