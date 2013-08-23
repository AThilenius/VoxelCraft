//
//  VCApplication.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"
#include "VCInput.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	void Initialize();
	void Run();

public:
	VCGLRenderer* Renderer;
	VCGameObject* RootNode;
    VCInput* Input;
    VCTime* Time;
    
    static VCApplication* Instance;

private:
    VCChunk* m_testChunk;
    
    MonoDomain *m_pRootDomain;
	MonoImage *m_pClassLibraryImage;
    
	MonoClass *m_pClassLibraryManagerClass;
	MonoObject *m_pClassLibraryManager;
};

