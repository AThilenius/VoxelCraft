#pragma once

#include "PCH.h"
#include "TestClass.h"
#include "VCVoxelShader.h"
#include "VCCamera.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render();

	static VCVoxelShader* VoxelShader;
	static VCCamera* MainCamera;

private:
	TestClass m_testClass;

};

