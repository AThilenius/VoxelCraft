//
//  VCGLWindow.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/14/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLWindow.h"
#include "VCObjectStore.h"
#include "VCGLFWInput.h"
#include "VCGLRenderer.h"
#include "VCLexicalEngine.h"
#include "VCGui.h"

VCGLWindow* VCGLWindow::ActiveWindow = NULL;
bool VCGLWindow::m_glfwWasInit = false;
VCGLWindow::GlfwToVCWindowMap VCGLWindow::m_glfwToVCWindowMap;
glfwFramebuferSizeHandler resizeHandler = NULL;

// =====   GLEW / GLFW Hooks   ======================================================
void _glewErrorCallback(int error, const char* description)
{
	VCLog::Error("GLFW Error Callback: " + std::string(description), "Initialize");
}

void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height)
{
	VCGLWindow* VcGlWinow = VCGLWindow::m_glfwToVCWindowMap[window];

	VcGlWinow->Width = width;
	VcGlWinow->Height = height;
	VcGlWinow->FullViewport = VCRectangle(0, 0, width, height);

	// Managed event
	resizeHandler(VcGlWinow->Handle, width, height);
	glViewport(0, 0, width, height);
}

// =====   VCGLWindow   ======================================================
VCGLWindow::VCGLWindow(void):
	Input(NULL),
	GLFWWindowHandle(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCGLWindow::~VCGLWindow(void)
{
	m_glfwToVCWindowMap.erase(GLFWWindowHandle);
}

VCGLWindow* VCGLWindow::GetWindowFromGLFW( GLFWwindow* window )
{
	return m_glfwToVCWindowMap[window];
}

void VCGLWindow::Initialize(int width, int height, std::string title)
{
	// =====   GLFW Static Init   ======================================================
	if (!m_glfwWasInit)
	{
		// GLFW
		if (!glfwInit())
		{
			VCLog::Error("Creating a Failed to initialize GLFW.", "Initialize");
			std::cin.ignore();
		}

		glfwSetErrorCallback(_glewErrorCallback);

		// Finish first-time init below ( I need a GLFW window to create an OpenGL context before I can init glew )
	}


	VCLog::Info("Creating a VCWindow...", "Initialize");

	//glfwWindowHint(GLFW_DECORATED, false);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	// =====   GLFW   ======================================================
	GLFWWindowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!GLFWWindowHandle)
	{
		glfwTerminate();
		VCLog::Error("Failed to create a window.", "Initialize");
		std::cin.ignore();
	}

	glfwMakeContextCurrent(GLFWWindowHandle);

	if (!m_glfwWasInit)
	{
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major); 
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		VCLog::Info("OpenGL version: " + std::to_string(major) + "." + std::to_string(minor), "Initialize");
		VCLog::Info("Hardware: " + std::string((char*)glGetString(GL_RENDERER)), "Initialize");
	}

	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);
	FullViewport = VCRectangle(0, 0, Width, Height);

	glfwSetFramebufferSizeCallback(GLFWWindowHandle, _glfwFramebuferSizeCallback);

	// =====   GLEW   ======================================================
	if(!m_glfwWasInit)
	{
		// GLEW
		glewExperimental = true;
		GLenum glewError = glewInit();
		if( glewError != GLEW_OK )
		{
			VCLog::Error("Error initializing GLEW!", "Initialize");
			std::cin.ignore();
		}

		m_glfwWasInit = true;
	}

	m_glfwToVCWindowMap.insert(GlfwToVCWindowMap::value_type(GLFWWindowHandle, this));



	// =====   Sub-Systems needed   ======================================================

	// Ensure a VCGLRenderer is on-line
	if ( VCGLRenderer::Instance == NULL )
	{
		VCGLRenderer::Instance = new VCGLRenderer();
		VCGLRenderer::Instance->Initialize();
	}

	// Ensure a VCLexEngine is on-line
	if ( VCLexicalEngine::Instance == NULL )
	{
		VCLexicalEngine::Instance = new VCLexicalEngine();
		VCLexicalEngine::Instance->Initialize();
	}

	// Ensure a VCGui is on-line
	if ( VCGui::Instance == NULL )
	{
		VCGui::Instance = new VCGui();
		VCGui::Instance->Initialize();
	}

	// =====   Finally   ======================================================
	Input = new VCGLFWInput(this);

	VCLog::Info("VCGLWindow Initialized.", "Initialize");
	glErrorCheck();
}

void VCGLWindow::Activate()
{
	ActiveWindow = this;
	glfwMakeContextCurrent(GLFWWindowHandle);
}


// =====   Interop   ======================================================

void VCInteropGLWindowPollEvents()
{
	glfwPollEvents();
}

int VCInteropGLWindowCreate( int width, int height, char* title )
{
	VCGLWindow* win = new VCGLWindow();
	win->Initialize(width, height, std::string(title));
	return win->Handle;
}

void VCInteropGLWindowRelease( int handle )
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropGLWindowActivate( int handle )
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	obj->Activate();
}

void VCInteropGLWindowSwapBuffers(int handle)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwSwapBuffers(obj->GLFWWindowHandle);
}

bool VCInteropGLWindowShouldClose(int handle)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	return glfwWindowShouldClose(obj->GLFWWindowHandle);
}

void VCInteropGLWindowVSync(int handle, int enabled)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	
	glfwMakeContextCurrent(obj->GLFWWindowHandle);

	if (enabled)
		glfwSwapInterval(1);

	else
		glfwSwapInterval(0);
}

void VCInteropGLWindowGetSize(int handle, int* width, int* height)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwGetWindowSize(obj->GLFWWindowHandle, width, height);
}

void VCInteropGLWindowSetSize(int handle, int width, int height)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwSetWindowSize(obj->GLFWWindowHandle, width, height);
	obj->Height = height;
	obj->Width = width;
	obj->FullViewport = VCRectangle(0, 0, width, height);
}

void VCInteropGLWindowGetPos(int handle, int* x, int* y)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwGetWindowPos(obj->GLFWWindowHandle, x, y);
}

void VCInteropGLWindowSetPos(int handle, int x, int y)
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwSetWindowPos(obj->GLFWWindowHandle, x, y);
}

void VCInteropGetMonitorSize(int* width, int* height)
{
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	*width = mode->width;
	*height = mode->height;
}

void VCInteropGLWindowRegisterResizeCallback(glfwFramebuferSizeHandler callback)
{
	resizeHandler = callback;
}