//
//  VCInputPreProcessor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCInputPreProcessor__
#define __VoxelCraftOSX__VCInputPreProcessor__

#include "PCH.h"

class VCMonoMethod;

class VCInput
{
public:
    VCInput();
    ~VCInput();
    
    void Initalize();

    // ================================      Interop      ============
public:
    int Handle;
    static void RegisterMonoHandlers();

	static VCMonoMethod* KeyCallback;
	static VCMonoMethod* MouseMoveCallback;
	static VCMonoMethod* MouseClickCallback;
	static VCMonoMethod* MouseEnterCallback;
	static VCMonoMethod* MouseScrollCallback;
};

void VCInteropInputGetMouse(float* x, float* y, bool* left, bool* right);
void VCInteropInputSetMouse(float x, float y);
bool VCInteropInputGetKey(int key);
void VCInteropInputSetCursorVisible(bool val);

#endif /* defined(__VoxelCraftOSX__VCInputPreProcessor__) */
