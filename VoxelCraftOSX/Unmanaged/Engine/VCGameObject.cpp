//
//  VCGameObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGameObject.h"
#import "VCSceneGraph.h"


VCGameObject::VCGameObject(void):
    Name ("UnNamed"),
    m_parent(NULL),
    Position(glm::vec3(0, 0, 0)),
    Rotation(glm::quat()),
    Scale(glm::vec3(1, 1, 1)),
    ModelMatrix(glm::mat4(1.0f))
{
    VCObjectStore::Instance->UpdatePointer(Handle, this);
    cout << "VCGameObject created with handle: " << Handle << endl;
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
    // Identity
	ModelMatrix = glm::mat4(1.0f);
    
	if (m_parent != NULL)
		ModelMatrix = m_parent->ModelMatrix;
    
    // Rotate, Translate, Scale
    ModelMatrix = glm::toMat4(Rotation);
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::scale(ModelMatrix, Scale.x, Scale.y, Scale.z);
    
    FOREACH(iter, Children)
        (*iter)->PreRender();
}

void VCGameObject::Render()
{   
    FOREACH(iter, Children)
        (*iter)->Render();
}

VCGameObject* VCGameObject::GetParent()
{
	return m_parent;
}

void VCGameObject::SetParent( VCGameObject* parent )
{
	if ( m_parent != NULL )
		m_parent->Children.erase(parent);
    
	m_parent = parent;
    
	if ( parent != NULL )
		parent->Children.insert(this);
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
    //VCCamera* obj = (VCCamera*) VCObjectStore::Instance->GetObject(handle);
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
    //VCCamera* obj = (VCCamera*) VCObjectStore::Instance->GetObject(handle);
    obj->Position = vec3(posX, posY, posZ);
    obj->Rotation = quat(rotX, rotY, rotZ, rotW);
    obj->Scale = vec3(sclX, sclY, sclZ);
}



