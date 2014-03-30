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

// =====   OpenGL Error Callback   ======================================================
void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
#ifdef SHOW_GL_WARNINGS
	char debSource[16], debType[20], debSev[5];
	if(source == GL_DEBUG_SOURCE_API_ARB)
		strcpy(debSource, "OpenGL");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
		strcpy(debSource, "Windows");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
		strcpy(debSource, "Shader Compiler");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
		strcpy(debSource, "Third Party");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
		strcpy(debSource, "Application");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
		strcpy(debSource, "Other");

	if(type == GL_DEBUG_TYPE_ERROR_ARB)
		strcpy(debType, "Error");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
		strcpy(debType, "Deprecated behavior");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
		strcpy(debType, "Undefined behavior");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
		strcpy(debType, "Portability");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
		strcpy(debType, "Performance");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)
		strcpy(debType, "Other");

	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
	{
		strcpy(debSev, "High");
		VCLog::Error("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");
	}

	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
	{
		strcpy(debSev, "Medium");
		VCLog::Error("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");
	}

	//else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
	//{
	//	static std::set<std::string> postedWarnings;

	//	strcpy(debSev, "Low");
	//	std::string post = std::string("Source:") + debSource + "\nType:" + debType + "\nID:" + std::to_string(id) + "\nSeverity:" + debSev + "\nMessage:" + message + "\n";

	//	if(postedWarnings.find(post) == postedWarnings.end())
	//	{
	//		VCLog::Warning("Source: " + std::string(debSource) + " Type: " + debType + " ID: " + std::to_string(id) + " Message: " + message, "OGLDebug");

	//		postedWarnings.insert(post);
	//	}
	//}

#endif
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
			VCLog::Error("Error initializing GLEW!", "Initialize");

		// Specify some OpenGL shit. This should be moved later ( Maybe make C# bindings for it )
#if DEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallbackARB(&glDebugCallback, NULL);
#endif

		glClearColor(0.85f, 0.87f, 0.898f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glDepthFunc(GL_LESS); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		glEnable(GL_CULL_FACE);

		m_glfwWasInit = true;
	}

	m_glfwToVCWindowMap.insert(GlfwToVCWindowMap::value_type(GLFWWindowHandle, this));



	// =====   Sub-Systems needed   ======================================================

	// Ensure a VCLexEngine is on-line
	if ( VCLexicalEngine::Instance == NULL )
	{
		VCLexicalEngine::Instance = new VCLexicalEngine();
		VCLexicalEngine::Instance->Initialize();
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

void VCInteropGLWindowSetTitle( int handle, char* title )
{
	VCGLWindow* obj = (VCGLWindow*) VCObjectStore::Instance->GetObject(handle);
	glfwSetWindowTitle(obj->GLFWWindowHandle, title);
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