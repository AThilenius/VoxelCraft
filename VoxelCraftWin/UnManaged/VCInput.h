//
//  VCInputPreProcessor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

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
	static VCMonoMethod* CharCallback;
	static VCMonoMethod* MouseMoveCallback;
	static VCMonoMethod* MouseClickCallback;
	static VCMonoMethod* MouseEnterCallback;
	static VCMonoMethod* MouseScrollCallback;
};

void VCInteropInputGetMouse(float* x, float* y);
void VCInteropInputSetMouse(float x, float y);
void VCInteropInputSetCursorVisible(bool val);