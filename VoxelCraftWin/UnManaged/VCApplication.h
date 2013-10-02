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


using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	virtual void Initialize();
    virtual void ShutDown();
    virtual void Step();

public:
    VCWindow* Window;
	VCGLRenderer* Renderer;
    VCSceneGraph* SceneGraph;
    VCInput* Input;
    VCTime* Time;
    VCObjectStore* ObjectStore;
    VCMonoRuntime* MonoRuntime;
	VCLexicalEngine* LexEngine;
    
    static VCApplication* Instance;
};

void SayHelloUnmanaged();
