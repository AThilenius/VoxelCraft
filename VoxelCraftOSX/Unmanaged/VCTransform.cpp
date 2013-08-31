//
//  VCTransform.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTransform.h"
#import "VCGameObject.h"


VCTransform::VCTransform(void)
{
    Handle = VCObjectStore::Instance->RegisterObject(this);
    cout << "VCTransform created with handle: " << Handle << endl;
    
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::quat();
	Scale = glm::vec3(1, 1, 1);
	ModelMatrix = glm::mat4(1.0f);
}

VCTransform::~VCTransform(void)
{
    VCObjectStore::Instance->ReleaseObject(Handle);
}

void VCTransform::PreRender()
{
	// Identity
	ModelMatrix = glm::mat4(1.0f);
    
	if (GameObject->GetParent() != NULL)
		ModelMatrix = GameObject->GetParent()->Transform->ModelMatrix;

    // Rotation
    ModelMatrix = glm::toMat4(Rotation);
    
	// Translation
	ModelMatrix = glm::translate(ModelMatrix, Position);
    
	// Scale
	ModelMatrix = glm::scale(ModelMatrix, Scale.x, Scale.y, Scale.z);	
}

vec3 VCTransform::Forward()
{
    return glm::normalize(Rotation * glm::vec3(0.0f, 0.0f, 1.0f));
}

vec3 VCTransform::Right()
{
    return glm::normalize(Rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

vec3 VCTransform::Up()
{
    return glm::normalize(Rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}

void VCTransform::Rotate(vec3 euler)
{
    quat rotQuat = quat(euler);
    Rotate(rotQuat);
}

void VCTransform::Rotate(quat quaternion)
{
    Rotation = quaternion * Rotation;
}

// ================================      Interop      ============
void VCTransform::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Transform::VCInteropNewTransform",                 (void*)VCInteropNewTransform);
    mono_add_internal_call("VCEngine.Transform::VCInteropReleaseTransform",             (void*)VCInteropReleaseTransform);
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformSetPosition",         (void*)VCInteropTransformSetPosition);
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformSetRotationEuler",    (void*)VCInteropTransformSetRotationEuler);
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformSetRotationQuat",     (void*)VCInteropTransformSetRotationQuat);
    mono_add_internal_call("VCEngine.Transform::VCInteropTransformSetScale",            (void*)VCInteropTransformSetScale);
}

int VCInteropNewTransform()
{
    VCTransform* newTransform = new VCTransform();
    return newTransform->Handle;
}

void VCInteropReleaseTransform(int handle)
{
    VCTransform* obj = (VCTransform*) VCObjectStore::Instance->GetObject(handle);
    delete obj;
}

void VCInteropTransformSetPosition(int handle, float x, float y, float z)
{
    VCTransform* obj = (VCTransform*) VCObjectStore::Instance->GetObject(handle);
    obj->Position = vec3(x, y, z);
}

void VCInteropTransformSetRotationEuler(int handle, float x, float y, float z)
{
    VCTransform* obj = (VCTransform*) VCObjectStore::Instance->GetObject(handle);
    obj->Rotation = quat(vec3(x, y, z));
}

void VCInteropTransformSetRotationQuat(int handle, float x, float y, float z, float w)
{
    VCTransform* obj = (VCTransform*) VCObjectStore::Instance->GetObject(handle);
    obj->Rotation = quat(x, y, z, w);
}

void VCInteropTransformSetScale(int handle, float x, float y, float z)
{
    VCTransform* obj = (VCTransform*) VCObjectStore::Instance->GetObject(handle);
    obj->Scale = vec3(x, y, z);
}

// ===============================================================

