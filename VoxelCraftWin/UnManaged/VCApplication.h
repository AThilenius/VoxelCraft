//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCWindow;
class VCGLRenderer;
class VCSceneGraph;
class VCInput;
class VCTime;
class VCObjectStore;
class VCMonoRuntime;
class VCLexicalEngine;
class VCGui;
class VCDebug;


using namespace std;

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
	VCDebug* Debug;
    
    static VCApplication* Instance;
};

void SayHelloUnmanaged();
