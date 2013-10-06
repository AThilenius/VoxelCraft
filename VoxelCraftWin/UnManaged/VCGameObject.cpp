//
//  VCGameObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGameObject.h"
#include "VCSceneGraph.h"


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
		m_parent->Children.erase(parent);
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
    mono_add_internal_call("VCEngine.GameObject::VCInteropNewGameObject",           (void*)VCInteropNewGameObject);
    mono_add_internal_call("VCEngine.GameObject::VCInteropReleaseGameObject",       (void*)VCInteropReleaseGameObject);
    
    // Parent / Children
    mono_add_internal_call("VCEngine.GameObject::VCInteropGameObjectSetParent",     (void*)VCInteropGameObjectSetParent);
    
    // Transform
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformGetData",         (void*)VCInteropTransformGetData);
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformSetData",         (void*)VCInteropTransformSetData);
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

// Transform
void VCInteropTransformGetData(int handle, float* posX, float* posY, float* posZ, float* rotX, float* rotY, float* rotZ, float* rotW, float* sclX, float* sclY, float* sclZ)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    vec3 pos = obj->Position;
    quat rot = obj->Rotation;
    vec3 scale = obj->Scale;
    
    *posX = pos.x;
    *posY = pos.y;
    *posZ = pos.z;
    
    *rotX = rot.x;
    *rotY = rot.y;
    *rotZ = rot.z;
    *rotW = rot.w;
    
    *sclX = scale.x;
    *sclY = scale.y;
    *sclZ = scale.z;
}

void VCInteropTransformSetData(int handle, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, float sclX, float sclY, float sclZ)
{
    VCGameObject* obj = (VCGameObject*) VCObjectStore::Instance->GetObject(handle);
    obj->Position = vec3(posX, posY, posZ);
    obj->Rotation = quat(rotW, rotX, rotY, rotZ);
    obj->Scale = vec3(sclX, sclY, sclZ);
	obj->MarkForRebuild();
    
    if ( true )
        return;
    
    cout << endl << "GameObject [" << handle << "] Set to: " << endl;
    cout << obj->Position.x << " " << obj->Position.y << " " << obj->Position.z << endl;
    cout << obj->Rotation.x << " " << obj->Rotation.y << " " << obj->Rotation.z << " " << obj->Rotation.w << endl;
    cout << obj->Scale.x << " " << obj->Scale.y << " " << obj->Scale.z << endl;
}