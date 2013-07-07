#include "VCTransform.h"


VCTransform::VCTransform(void)
{
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	ModelMatrix = glm::mat4(1.0f);

	m_parent = NULL;
}

VCTransform::~VCTransform(void)
{
}

VCTransform* VCTransform::GetParent()
{
	return m_parent;
}

void VCTransform::SetParent( VCTransform* parent )
{
	if ( m_parent != NULL )
		m_parent->m_children.erase(parent);

	m_parent = parent;

	if ( parent != NULL )
		parent->m_children.insert(parent);
}

void VCTransform::PreRender()
{
	// Identity
	ModelMatrix = glm::mat4(1.0f);

	if (m_parent)
		ModelMatrix = m_parent->ModelMatrix;

	// Scale
	ModelMatrix = glm::scale(ModelMatrix, Scale.x, Scale.y, Scale.z);

	// Translation
	ModelMatrix = glm::translate(ModelMatrix, Position);

	// Rotation
	ModelMatrix = glm::rotate( ModelMatrix, Rotation.x, glm::vec3(1, 0, 0) );
	ModelMatrix = glm::rotate( ModelMatrix, Rotation.y, glm::vec3(0, 1, 0) );
	ModelMatrix = glm::rotate( ModelMatrix, Rotation.z, glm::vec3(0, 0, 1) );
}
