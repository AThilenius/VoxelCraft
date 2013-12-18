//
//  VCMonoRuntime.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct _MonoClass;
struct _MonoDomain;
struct _MonoImage;
struct _MonoMethod;
typedef struct _MonoClass MonoClass;
typedef struct _MonoDomain MonoDomain;
typedef struct _MonoImage MonoImage;
typedef struct _MonoMethod MonoMethod;
class VCMonoMethod;

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
    static MonoDomain* m_pRootDomain;
	static MonoImage* m_assemblyImage;

	MonoMethod* m_editorEntry;
	MonoMethod* m_gameEntry;
};