//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCGLWindow.h"
#include "VCObjectStore.h"
#include "VCInput.h"
#include "VCGLRenderer.h"
#include "VCLexicalEngine.h"
#include "VCGui.h"
#include "VCTime.h"

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
    virtual void ShutDown();

public:
    VCInput* Input;
	VCGLRenderer* Renderer;
    VCObjectStore* ObjectStore;
	VCLexicalEngine* LexEngine;
	VCGui* Gui;
    
    static VCApplication* Instance;
};

DLL_EXPORT_API void VCInteropInitalizeWindow();
DLL_EXPORT_API void VCInteropInitalizeObjectStore();
DLL_EXPORT_API void VCInteropInitalizeInput();
DLL_EXPORT_API void VCInteropInitalizeRenderer();
DLL_EXPORT_API void VCInteropInitalizeLexEngine();
DLL_EXPORT_API void VCInteropInitalizeGui();