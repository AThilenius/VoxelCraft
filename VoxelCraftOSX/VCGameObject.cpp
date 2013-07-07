#include "VCGameObject.h"

#include "VCTransform.h"


VCGameObject::VCGameObject(void)
{
	this->GameObject = this;
	this->Transform = new VCTransform();

	AttachComponent(Transform);
}

VCGameObject::~VCGameObject(void)
{
}


// Not how I should do this...

void VCGameObject::Start()
{
	FOREACH (iter, m_components)
		(*iter)->Start();
}

void VCGameObject::Update()
{
	FOREACH (iter, m_components)
		(*iter)->Update();
}

void VCGameObject::LateUpdate()
{
	FOREACH (iter, m_components)
		(*iter)->LateUpdate();
}

void VCGameObject::Gui()
{
	FOREACH (iter, m_components)
		(*iter)->Gui();
}

void VCGameObject::PreRender()
{
	FOREACH (iter, m_components)
		(*iter)->PreRender();
}

void VCGameObject::AttachComponent ( VCComponent* component )
{
	component->GameObject = this;
	component->Transform = this->Transform;

	m_components.insert( component );
}