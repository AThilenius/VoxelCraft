//
//  VCGameObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGameObject.h"
#import "VCTransform.h"


VCGameObject::VCGameObject(void)
{
    Handle = VCObjectStore::Instance->RegisterObject(this);
    cout << "VCGameObjects created with handle: " << Handle << endl;
    
	this->Transform = new VCTransform();
    AttachComponent(Transform);
    
    Name = "UnNamed";
    m_parent = NULL;
}

VCGameObject::~VCGameObject(void)
{
    VCObjectStore::Instance->ReleaseObject(Handle);
}

void VCGameObject::Start()
{
	FOREACH (iter, m_components)
		(*iter)->Start();
    
    FOREACH(iter, m_children)
        (*iter)->Start();
}

void VCGameObject::Update()
{
	FOREACH (iter, m_components)
        (*iter)->Update();
    
    FOREACH(iter, m_children)
        (*iter)->Update();
}

void VCGameObject::LateUpdate()
{
	FOREACH (iter, m_components)
        (*iter)->LateUpdate();
    
    FOREACH(iter, m_children)
        (*iter)->LateUpdate();
}

void VCGameObject::Gui()
{
	FOREACH (iter, m_components)
        (*iter)->Gui();
    
    FOREACH(iter, m_children)
        (*iter)->Gui();
}

void VCGameObject::PreRender()
{
	FOREACH (iter, m_components)
        (*iter)->PreRender();
    
    FOREACH(iter, m_children)
        (*iter)->PreRender();
}

void VCGameObject::Render()
{
    FOREACH (iter, m_components)
        (*iter)->Render();
    
    FOREACH(iter, m_children)
        (*iter)->Render();
}

void VCGameObject::AttachComponent ( VCComponent* component )
{
	component->GameObject = this;
	component->Transform = this->Transform;

	m_components.insert( component );
}

VCGameObject* VCGameObject::GetParent()
{
	return m_parent;
}

void VCGameObject::SetParent( VCGameObject* parent )
{
	if ( m_parent != NULL )
		m_parent->m_children.erase(parent);
    
	m_parent = parent;
    
	if ( parent != NULL )
		parent->m_children.insert(this);
}


// ================================      Interop      ============
void VCGameObject::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.GameObject::VCInteropNewGameObject",               (void*)VCInteropNewGameObject);
    mono_add_internal_call("VCEngine.GameObject::VCInteropReleaseGameObject",           (void*)VCInteropReleaseGameObject);
    mono_add_internal_call("VCEngine.GameObject::VCInteropGameObjectAttachComponent",   (void*)VCInteropGameObjectAttachComponent);
    mono_add_internal_call("VCEngine.GameObject::VCInteropGameObjectSetParent",         (void*)VCInteropGameObjectSetParent);
    mono_add_internal_call("VCEngine.GameObject::VCInteropGameObjectGetParent",         (void*)VCInteropGameObjectGetParent);
    mono_add_internal_call("VCEngine.GameObject::VCInteropGameObjectGetTransform",      (void*)VCInteropGameObjectGetTransform);
}

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

void VCInteropGameObjectAttachComponent(int handle, int componentHandle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    obj->AttachComponent((VCComponent*) VCObjectStore::Instance->GetObject(componentHandle));
}

void VCInteropGameObjectSetParent(int handle, int parentHandle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    obj->SetParent((VCGameObject*) VCObjectStore::Instance->GetObject(parentHandle));
}

int VCInteropGameObjectGetParent(int handle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    VCGameObject* parent = obj->GetParent();
    
    if ( parent == NULL )
        return -1;
    else
        return parent->Handle;
}

int VCInteropGameObjectGetTransform(int handle)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    return obj->Transform->Handle;
}




