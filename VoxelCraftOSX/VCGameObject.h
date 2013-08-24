//
//  VCGameObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#import "PCH.h"
#import "VCComponent.h"
#import "VCSceneGraph.h"

class VCTransform;

// Container class for any game object.
class VCGameObject
{
public:
	VCGameObject(void);
    VCGameObject(VCGameObject* parent);
	~VCGameObject(void);

	void AttachComponent ( VCComponent* component );
    
    void SetParent ( VCGameObject* parent );
	VCGameObject* GetParent();
	
public:
    string Name;
    VCTransform* Transform;

private:
    void Start();
    void Update();
    void LateUpdate();
    void Gui();
    void PreRender();
    void Render();
    
    friend class VCSceneGraph;
    
private:
    VCGameObject* m_parent;
	std::unordered_set<VCComponent*> m_components;
	std::unordered_set<VCGameObject*> m_children;
};

