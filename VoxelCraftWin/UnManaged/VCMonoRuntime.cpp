//
//  VCMonoBinder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCMonoRuntime.h"
#include "PathUtil.h"

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
	//cout << "MonoRuntime setting directories to:" << endl;
	//cout << "Library: " << PathUtil::GetLibDirectory() << endl;
	//cout << "Config: " << PathUtil::GetConfigDirectory() << endl;
	//cout << "Game Library: " << PathUtil::GetBinDirectory().append("VCEngine.dll") << endl;

	mono_set_dirs(PathUtil::GetLibDirectory().c_str(), PathUtil::GetConfigDirectory().c_str());
	
	// Required for mdb's to load for detailed stack traces etc.
	mono_debug_init(MONO_DEBUG_FORMAT_MONO);

    VCMonoRuntime::m_pRootDomain = mono_jit_init_version("MonoApplication", "v4.0.30319");
    
    // Setup Bindings
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
	VCPhysics::RegisterMonoHandlers();
	VCGui::RegisterMonoHandlers();
	VCLexicalEngine::RegisterMonoHandlers();
	VCGLRenderer::RegisterMonoHandlers();
	VCWindow::RegisterMonoHandlers();
	VCWorld::RegisterMonoHandlers();
}

void VCMonoRuntime::EditorMain()
{
	mono_runtime_invoke(m_editorEntry, NULL, NULL, NULL);
}

void VCMonoRuntime::GameMain()
{
	mono_runtime_invoke(m_gameEntry, NULL, NULL, NULL);
}

VCMonoMethod* VCMonoRuntime::GetMonoMethod( string className, string method )
{
	ostringstream oss;
	oss << "VCEngine.";
	oss << className;
	oss << ":";
	oss << method;

	MonoClass* mClass = mono_class_from_name(m_assemblyImage, "VCEngine", className.c_str());
	MonoMethodDesc* mMethidDesc = mono_method_desc_new (oss.str().c_str(), true);
	MonoMethod* mMethod = mono_method_desc_search_in_class (mMethidDesc, mClass);

	if(mMethod == NULL)
	{
		VC_ERROR("Failed to load managed method: " << method << " in class: " << className);
	}

	return new VCMonoMethod(mMethod);
}


