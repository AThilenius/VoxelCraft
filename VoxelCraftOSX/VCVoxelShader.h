#pragma once

#include "PCH.h"
#include "Shader.h"

using namespace std;

class VCVoxelShader : public Shader
{
public:
	VCVoxelShader(void);
	~VCVoxelShader(void);

	void SetModelMatrix(glm::mat4 modelMatrix);
	void SetLightPosition(glm::vec3 position);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifMVP;
	GLint m_unifNormal;
	GLint m_unifLightPos;
};

