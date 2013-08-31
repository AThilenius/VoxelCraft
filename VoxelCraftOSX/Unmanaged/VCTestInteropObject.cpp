//
//  VCTestInteropObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTestInteropObject.h"

void VCTestInteropObject::RegisterMonoBindings()
{
    mono_add_internal_call("VCEngine.TestInteropObject::VCNewTestInteropObject",            (void*) VCNewTestInteropObject);
    mono_add_internal_call("VCEngine.TestInteropObject::VCReleaseTestInteropObject",        (void*) VCReleaseTestInteropObject);
    mono_add_internal_call("VCEngine.TestInteropObject::VCTestInteropObjectSetLocation",    (void*) VCTestInteropObjectSetLocation);
}

VCTestInteropObject::VCTestInteropObject()
{
    cout << "UnManaged: VCTestInteropObject CTor called" << endl;
}

VCTestInteropObject::~VCTestInteropObject()
{
    cout << "UnManaged: VCTestInteropObject DTor called" << endl;
}

void VCTestInteropObject::SetLocation(float x, float y, float z)
{
    cout << "UnManaged: Seting objects location to " << x << ", " << y << ", " << z << endl;
}

// Interop bindings
int VCNewTestInteropObject()
{
    VCTestInteropObject* newObj = new VCTestInteropObject();
    return VCObjectStore::Instance->RegisterObject(newObj);
}

void VCReleaseTestInteropObject(int handle)
{
    VCTestInteropObject* obj = (VCTestInteropObject*) VCObjectStore::Instance->GetObject(handle);
    VCObjectStore::Instance->ReleaseObject(handle);
    delete obj;
}

void VCTestInteropObjectSetLocation(int handle, float x, float y, float z)
{
    VCTestInteropObject* obj = (VCTestInteropObject*) VCObjectStore::Instance->GetObject(handle);
    obj->SetLocation(x, y, z);
}