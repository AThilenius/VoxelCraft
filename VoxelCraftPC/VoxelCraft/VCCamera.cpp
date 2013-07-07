#include "VCCamera.h"


VCCamera::VCCamera(void)
{
}


VCCamera::~VCCamera(void)
{
}

float rotation = 0.0f;

void VCCamera::PreRender()
{
	ProjectionMatrix = glm::perspective(65.0f, 4.0f / 3.0f, 0.1f, 400.0f);
	ViewMatrix = glm::translate(0.0f, 0.0f, -100.0f);
	ViewMatrix = glm::rotate(ViewMatrix, rotation, 1.0f, 1.0f, 1.0f );

	ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;

	rotation += 0.1;
}
