//
//  VCMonoRuntime.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMonoRuntime.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

#include "PathUtil.h"
#include "VCFlatGenerator.h"
#include "VCNoiseGenerator.h"
#include "VCInput.h"
#include "VCCamera.h"
#include "VCGameObject.h"
#include "VCGui.h"
#include "VCLexicalEngine.h"
#include "VCWindow.h"
#include "VCGLRenderer.h"
#include "VCWorld.h"
#include "VCMonoMethod.h"
#include "VC3DLineDrawer.h"

VCMonoRuntime* VCMonoRuntime::Instance = NULL;
MonoDomain* VCMonoRuntime::m_pRootDomain;
MonoImage* VCMonoRuntime::m_assemblyImage;

VCMonoRuntime::VCMonoRuntime()
{
    VCMonoRuntime::Instance = this;
}

VCMonoRuntime::~VCMonoRuntime()
{
    
}

void VCMonoRuntime::Initalize()
{
	mono_set_dirs(PathUtil::GetLibDirectory().c_str(), PathUtil::GetConfigDirectory().c_str());
	
	//const char* options[] = {"--debugger-agent=transport=dt_socket,address=127.0.0.1:10000"};
	//mono_jit_parse_options(1, (char**)options);

	// Required for mdb's to load for detailed stack traces etc.
	mono_debug_init(MONO_DEBUG_FORMAT_MONO);

	m_pRootDomain = mono_jit_init_version("MonoApplication", "v4.0.30319");
	
    Bind();
    
    // Assembly
	MonoAssembly *pMonoAssembly = mono_domain_assembly_open(mono_domain_get(), PathUtil::GetBinDirectory().append("VCEngine.dll").c_str() );
	m_assemblyImage = mono_assembly_get_image(pMonoAssembly);
    
    // Class
	//m_engineType = mono_class_from_name(m_assemblyImage, "VCEngine", "VCEngineCore");
	//m_engineInstance = mono_object_new(mono_domain_get(), m_engineType);

    // Instantiate6
    //mono_runtime_object_init(m_engineInstance);

	// Editor
	MonoClass* editorClass = mono_class_from_name(m_assemblyImage, "VCEngine", "Editor");
	MonoMethodDesc* editorEntryPoint = mono_method_desc_new ("VCEngine.Editor:EditorMain()", true);
	m_editorEntry = mono_method_desc_search_in_class (editorEntryPoint, editorClass);

	// Game
	MonoClass* gameClass = mono_class_from_name(m_assemblyImage, "VCEngine", "Game");
	MonoMethodDesc* gameEntryPoint = mono_method_desc_new ("VCEngine.Game:GameMain()", true);
	m_gameEntry = mono_method_desc_search_in_class (gameEntryPoint, gameClass);
}

void VCMonoRuntime::Bind()
{
    // Registry
    VCGameObject::RegisterMonoHandlers();
    VCCamera::RegisterMonoHandlers();
    VCInput::RegisterMonoHandlers();
	VCGui::RegisterMonoHandlers();
	VCLexicalEngine::RegisterMonoHandlers();
	VCGLRenderer::RegisterMonoHandlers();
	VCWindow::RegisterMonoHandlers();
	VCWorld::RegisterMonoHandlers();
	VC3DLineDrawer::RegisterMonoHandlers();
}

//void VCMonoRuntime::EditorMain()
//{
//	mono_runtime_invoke(m_editorEntry, NULL, NULL, NULL);
//}

//void VCMonoRuntime::GameMain()
//{
//	mono_runtime_invoke(m_gameEntry, NULL, NULL, NULL);
//}

//VCMonoMethod* VCMonoRuntime::GetMonoMethod( std::string className, std::string method )
//{
//	std::ostringstream oss;
//	oss << "VCEngine.";
//	oss << className;
//	oss << ":";
//	oss << method;
//
//	MonoClass* mClass = mono_class_from_name(m_assemblyImage, "VCEngine", className.c_str());
//	MonoMethodDesc* mMethidDesc = mono_method_desc_new (oss.str().c_str(), true);
//	MonoMethod* mMethod = mono_method_desc_search_in_class (mMethidDesc, mClass);
//
//	if(mMethod == NULL)
//	{
//		VC_ERROR("Failed to load managed method: " << method << " in class: " << className);
//	}
//
//	return new VCMonoMethod(mMethod);
//}

void VCMonoRuntime::SetMethod( std::string classMethodName, const void* method )
{
//	mono_add_internal_call(("VCEngine." + classMethodName).c_str(), method);
}