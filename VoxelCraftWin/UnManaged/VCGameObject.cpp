//
//  VCGameObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGameObject.h"

#include "VCSceneGraph.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"


VCGameObject::VCGameObject(void):
    Name ("UnNamed"),
    m_parent(NULL),
    Position(glm::vec3(0, 0, 0)),
    Rotation(glm::quat()),
    Scale(glm::vec3(1, 1, 1)),
    ModelMatrix(glm::mat4(1.0f)),
	m_rebuildNeeded(true)
{
    VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCGameObject::~VCGameObject(void)
{
}

void VCGameObject::Start()
{
    FOREACH(iter, Children)
        (*iter)->Start();
}

void VCGameObject::Update()
{
    FOREACH(iter, Children)
        (*iter)->Update();
}

void VCGameObject::LateUpdate()
{
    FOREACH(iter, Children)
        (*iter)->LateUpdate();
}

void VCGameObject::Gui()
{
    FOREACH(iter, Children)
        (*iter)->Gui();
}

void VCGameObject::PreRender()
{   
	if (m_rebuildNeeded)
	{
		m_rebuildNeeded = false;

		// Rotate, Translate, Scale
		ModelMatrix = glm::toMat4(Rotation);
		ModelMatrix = glm::translate(ModelMatrix, Position);
		ModelMatrix = glm::scale(ModelMatrix, Scale.x, Scale.y, Scale.z);
    
		if (m_parent != NULL)
			ModelMatrix = ModelMatrix * m_parent->ModelMatrix;
	}
    
    FOREACH(iter, Children)
         (*iter)->PreRender();
}

VCGameObject* VCGameObject::GetParent()
{
	return m_parent;
}

void VCGameObject::SetParent( VCGameObject* parent )
{
	if ( m_parent != NULL )
	{
		m_parent->Children.erase(this);
		m_parent->MarkForRebuild();
	}
    
	m_parent = parent;
    
	if ( parent != NULL )
	{
		parent->Children.insert(this);
		parent->MarkForRebuild();
	}
}

// ================================      Interop      ============
void VCGameObject::RegisterMonoHandlers()
{
    // CTor / DTor
    VCMonoRuntime::SetMethod("GameObject::VCInteropNewGameObject",           (void*)VCInteropNewGameObject);
	VCMonoRuntime::SetMethod("GameObject::VCInteropNewGameObject", (void*)VCInteropNewGameObject);
    VCMonoRuntime::SetMethod("GameObject::VCInteropReleaseGameObject",       (void*)VCInteropReleaseGameObject);
    
    // Parent / Children
    VCMonoRuntime::SetMethod("GameObject::VCInteropGameObjectSetParent",     (void*)VCInteropGameObjectSetParent);
    
    // Transform
	VCMonoRuntime::SetMethod("Transform::VCInteropTransformGetPosition",         (void*)VCInteropTransformGetPosition);
	VCMonoRuntime::SetMethod("Transform::VCInteropTransformGetRotation",         (void*)VCInteropTransformGetRotation);
	VCMonoRuntime::SetMethod("Transform::VCInteropTransformGetScale",         (void*)VCInteropTransformGetScale);

	VCMonoRuntime::SetMethod("Transform::VCInteropTransformSetPosition",         (void*)VCInteropTransformSetPosition);
	VCMonoRuntime::SetMethod("Transform::VCInteropTransformSetRotation",         (void*)VCInteropTransformSetRotation);
	VCMonoRuntime::SetMethod("Transform::VCInteropTransformSetScale",         (void*)VCInteropTransformSetScale);
}

// CTor / DTor
int VCInteropNewGameObject()
{
    VCGameObject* newGO = new VCGameObject();
    newGO->SetParent(VCSceneGraph::Instance->RootNode);
    return newGO->Handle;
}

void VCInteropReleaseGameObject(int handle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    delete obj;
}

// Parent / Child
void VCInteropGameObjectSetParent(int handle, int parentHandle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    obj->SetParent((VCGameObject*) VCObjectStore::Instance->GetObject(parentHandle));
}

glm::vec3 VCInteropTransformGetPosition( int handle )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	return obj->Position;
}

glm::quat VCInteropTransformGetRotation( int handle )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	return obj->Rotation;
}

glm::vec3 VCInteropTransformGetScale( int handle )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	return obj->Scale;
}

void VCInteropTransformSetPosition( int handle, glm::vec3 pos )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	obj->Position = pos;
	obj->MarkForRebuild();
}

void VCInteropTransformSetRotation( int handle, glm::quat rot )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	obj->Rotation = rot;
	obj->MarkForRebuild();
}

void VCInteropTransformSetScale( int handle, glm::vec3 scale )
{
	VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
	obj->Scale = scale;
	obj->MarkForRebuild();
}
