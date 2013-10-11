//
//  VCGameObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCMarshalableObject.h"

// Container class for any game object.
class VCGameObject : public VCMarshalableObject
{
public:
    VCGameObject(void);
	~VCGameObject(void);
    
    void SetParent ( VCGameObject* parent );
	VCGameObject* GetParent();
	void MarkForRebuild() { m_rebuildNeeded = true; }
    
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Gui();
    virtual void PreRender();
	
public:
    string Name;
    vec3 Position;
    quat Rotation;
    vec3 Scale;
    
    mat4 ModelMatrix;
    
	std::unordered_set<VCGameObject*> Children;
    
private:
    VCGameObject* m_parent;
	bool m_rebuildNeeded;
    
    // ================================      Interop      ============
public:
    static void RegisterMonoHandlers();
    
private:
    friend int VCInteropNewGameObject();
    friend void VCInteropReleaseGameObject(int handle);
    
    friend void VCInteropGameObjectSetParent(int handle, int parentHandle);
    // ===============================================================
};


// Interop
int VCInteropNewGameObject();
void VCInteropReleaseGameObject(int handle);

void VCInteropGameObjectSetParent(int handle, int parentHandle);

// Transform
vec3 VCInteropTransformGetPosition(int handle);
quat VCInteropTransformGetRotation(int handle);
vec3 VCInteropTransformGetScale(int handle);

void VCInteropTransformSetPosition(int handle, vec3 pos );
void VCInteropTransformSetRotation(int handle, quat rot );
void VCInteropTransformSetScale(int handle, vec3 scale );