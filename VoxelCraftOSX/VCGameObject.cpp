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
	this->Transform = new VCTransform();
    AttachComponent(Transform);
    
    Name = "UnNamed";
    m_parent = NULL;
	
    SetParent(VCSceneGraph::Instance->RootNode);
}

VCGameObject::VCGameObject(VCGameObject* parent)
{
    this->Transform = new VCTransform();
    AttachComponent(Transform);
    
    Name = "UnNamed";
    m_parent = NULL;
    
    SetParent(parent);
}

VCGameObject::~VCGameObject(void)
{
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