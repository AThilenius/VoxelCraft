//
//  VCMonoRuntime.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCMonoBinder__
#define __VoxelCraftOSX__VCMonoBinder__

#include "PCH.h"

#include "VCGui.h"
#include "VCLexicalEngine.h"
#include "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCWorld.h"
#include <string>
#include "VCMonoMethod.h"

class VCMonoRuntime
{
public:
    VCMonoRuntime();
    ~VCMonoRuntime();
    
    void Initalize();
    
	void EditorMain();
	void GameMain();

	static VCMonoMethod* GetMonoMethod (std::string className, std::string method);
	static void SetMethod (std::string classMethodName, const void* method);

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
