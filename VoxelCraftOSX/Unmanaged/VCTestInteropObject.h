//
//  VCTestInteropObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCTestInteropObject__
#define __VoxelCraftOSX__VCTestInteropObject__

#import "PCH.h"
#import "VCObjectStore.h"

class VCTestInteropObject
{
public:
    static void RegisterMonoBindings();
    void SetLocation (float x, float y, float z);
    
private:
    VCTestInteropObject();
    ~VCTestInteropObject();
    
    // Interop friends
    friend int VCNewTestInteropObject();
    friend void VCReleaseTestInteropObject(int handle);
    friend void VCTestInteropObjectSetLocation(int handle, float x, float y, float z);
    
};

// Interop bindings
int VCNewTestInteropObject();
void VCReleaseTestInteropObject(int handle);
void VCTestInteropObjectSetLocation(int handle, float x, float y, float z);

#endif /* defined(__VoxelCraftOSX__VCTestInteropObject__) */
