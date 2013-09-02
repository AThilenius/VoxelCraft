//
//  VCGameObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#import "PCH.h"
#import "VCMarshalableObject.h"

// Container class for any game object.
class VCGameObject : public VCMarshalableObject
{
public:
    VCGameObject(void);
	~VCGameObject(void);
    
    void SetParent ( VCGameObject* parent );
	VCGameObject* GetParent();
    
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Gui();
    virtual void PreRender();
    virtual void Render();
	
public:
    string Name;
    vec3 Position;
    quat Rotation;
    vec3 Scale;
    
    mat4 ModelMatrix;
    
	std::unordered_set<VCGameObject*> Children;
    
private:
    VCGameObject* m_parent;
    
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
void VCInteropTransformGetData(int handle, float* posX, float* posY, float* posZ, float* rotX, float* rotY, float* rotZ, float* rotW, float* sclX, float* sclY, float* sclZ);
void VCInteropTransformSetData(int handle, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, float sclX, float sclY, float sclZ);



