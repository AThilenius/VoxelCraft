//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMonoRuntime.h"
#include "VCWindow.h"
#include "VCObjectStore.h"
#include "VCInput.h"
#include "VCGLRenderer.h"
#include "VCLexicalEngine.h"
#include "VCGui.h"
#include "VCTime.h"
#include "VCSceneGraph.h"

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	virtual void Initialize();
	virtual void EditorMain();
	virtual void GameMain();
    virtual void ShutDown();

public:
    VCWindow* Window;
	VCGLRenderer* Renderer;
    VCSceneGraph* SceneGraph;
    VCInput* Input;
    VCTime* Time;
    VCObjectStore* ObjectStore;
    VCMonoRuntime* MonoRuntime;
	VCLexicalEngine* LexEngine;
	VCGui* Gui;
    
    static VCApplication* Instance;
};
