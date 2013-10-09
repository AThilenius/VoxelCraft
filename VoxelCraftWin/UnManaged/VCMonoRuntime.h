//
//  VCMonoBinder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCMonoBinder__
#define __VoxelCraftOSX__VCMonoBinder__

#include "PCH.h"

#include "VCCamera.h"
#include "VCGameObject.h"
#include "VCGui.h"
#include "VCLexicalEngine.h"
#include "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCWorld.h"
#include "VCMonoMethod.h"

class VCMonoRuntime
{
public:
    VCMonoRuntime();
    ~VCMonoRuntime();
    
    void Initalize();
    
	void EditorMain();
	void GameMain();

	static VCMonoMethod* GetMonoMethod (string className, string method);

	static VCMonoRuntime* Instance;
    
private:
    void Bind();
    
private:
    static MonoDomain *m_pRootDomain;
	static MonoImage *m_assemblyImage;

	MonoMethod* m_editorEntry;
	MonoMethod* m_gameEntry;
};

#endif /* defined(__VoxelCraftOSX__VCMonoBinder__) */
