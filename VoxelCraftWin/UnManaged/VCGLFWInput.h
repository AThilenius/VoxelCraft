//
//  VCInputPreProcessor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLWindow;

class VCGLFWInput
{
public:
    VCGLFWInput(VCGLWindow* window);
    ~VCGLFWInput();

    // ================================      Interop      ============
public:
    int Handle;
};
DLL_EXPORT_API void VCInteropGLFWInputSetMouse(int windowHandle, float x, float y);
DLL_EXPORT_API void VCInteropGLFWInputSetCursorVisible(int windowHandle, bool val);

typedef void (*GlfwKeyCallback)(int, int, int, int, int);
typedef void (*GlfwCharCallback)(int, unsigned int);
typedef void (*GlfwMouseMoveCallback)(int, double, double);
typedef void (*GlfwMouseClickCallback)(int, int, int, int);
typedef void (*GlfwMouseEnterCallback)(int, int);
typedef void (*GlfwMouseScrollCallback)(int, double, double);

DLL_EXPORT_API void VCInteropInputSetCallbacks(GlfwKeyCallback keyCallback, 
											   GlfwCharCallback charCallback, 
											   GlfwMouseMoveCallback mouseMoveCallback, 
											   GlfwMouseClickCallback mouseClickCallback,
											   GlfwMouseEnterCallback mouseEnterCallback,
											   GlfwMouseScrollCallback mouseScrollCallback);