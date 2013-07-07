#pragma once

#include "PCH.h"
#include "VCVoxelShader.h"
#include "VCChunk.h"


class TestClass
{
public:
	TestClass(void);
	~TestClass(void);

	void Initialize();
	void Render();

private:
	GLuint m_bufferId;
	VCChunk* m_chunk;
};

