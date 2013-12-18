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
};
DLL_EXPORT_API void VCInteropInputSetMouse(float x, float y);
DLL_EXPORT_API void VCInteropInputSetCursorVisible(bool val);

typedef void (*GlfwKeyCallback)(int, int, int, int);
typedef void (*GlfwCharCallback)(unsigned int);
typedef void (*GlfwMouseMoveCallback)(double, double);
typedef void (*GlfwMouseClickCallback)(int, int, int);
typedef void (*GlfwMouseEnterCallback)(int);
typedef void (*GlfwMouseScrollCallback)(double, double);

DLL_EXPORT_API void VCInteropInputSetCallbacks(GlfwKeyCallback keyCallback, 
											   GlfwCharCallback charCallback, 
											   GlfwMouseMoveCallback mouseMoveCallback, 
											   GlfwMouseClickCallback mouseClickCallback,
											   GlfwMouseEnterCallback mouseEnterCallback,
											   GlfwMouseScrollCallback mouseScrollCallback);