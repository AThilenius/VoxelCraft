#pragma once

#include "PCH.h"
#include "VCGLRenderer.h"
#include "VCChunk.h"
#include "VCGameObject.h"

using namespace std;

class VCApplication
{
public:
	VCApplication(void);
	~VCApplication(void);
	void Initialize();
	void Run();

public:
	VCGLRenderer* Renderer;
	VCGameObject* RootNode;

private:
	GLFWwindow* m_window;
};

