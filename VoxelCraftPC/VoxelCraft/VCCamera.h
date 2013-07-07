#pragma once

#include "PCH.h"


class VCCamera
{
public:
	VCCamera(void);
	~VCCamera(void);

	void PreRender();

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	glm::mat4 ProjectionViewMatrix;

};

