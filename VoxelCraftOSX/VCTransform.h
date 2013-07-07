#pragma once

#include "PCH.h"
#include "VCComponent.h"


class VCTransform;

class VCTransform : public VCComponent
{
public:
	VCTransform(void);
	~VCTransform(void);

	virtual void PreRender();
	VCTransform* GetParent();
	void SetParent ( VCTransform* parent );

public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 ModelMatrix;

private:
	VCTransform* m_parent;
	std::unordered_set<VCTransform*> m_children;

	
};

