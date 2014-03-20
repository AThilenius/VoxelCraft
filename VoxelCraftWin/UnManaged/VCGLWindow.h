//
//  VCGLWindow.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/14/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLFWInput;

#include "VCMarshalableObject.h"

class VCGLWindow : public VCMarshalableObject
{
public:
	VCGLWindow();
	~VCGLWindow();

	static VCGLWindow* GetWindowFromGLFW(GLFWwindow* Window);
	void Initialize(int width, int height, std::string title);
	void Activate();

public:
	static VCGLWindow* ActiveWindow;
	GLFWwindow* GLFWWindowHandle;
	VCRectangle FullViewport;
	VCGLFWInput* Input;
	int Width;
	int Height;

private:
	static bool m_glfwWasInit;

	typedef std::unordered_map<GLFWwindow*, VCGLWindow*> GlfwToVCWindowMap;
	static GlfwToVCWindowMap m_glfwToVCWindowMap;

private:
	friend void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height);
};

// Interop
DLL_EXPORT_API void VCInteropGLWindowPollEvents();
DLL_EXPORT_API void VCInteropGetMonitorSize(int* width, int* height );

DLL_EXPORT_API int VCInteropGLWindowCreate(int width, int height, char* title);
DLL_EXPORT_API void VCInteropGLWindowRelease(int handle);

DLL_EXPORT_API void VCInteropGLWindowActivate(int handle);
DLL_EXPORT_API void VCInteropGLWindowSwapBuffers(int handle);
DLL_EXPORT_API bool VCInteropGLWindowShouldClose(int handle);
DLL_EXPORT_API void VCInteropGLWindowVSync(int handle, int enabled); 
DLL_EXPORT_API void VCInteropGLWindowGetSize(int handle, int* width, int* height);
DLL_EXPORT_API void VCInteropGLWindowSetSize(int handle, int width, int height);
DLL_EXPORT_API void VCInteropGLWindowGetPos(int handle, int* x, int* y);
DLL_EXPORT_API void VCInteropGLWindowSetPos(int handle, int x, int y);

typedef void (*glfwFramebuferSizeHandler)(int, int, int);
DLL_EXPORT_API void VCInteropGLWindowRegisterResizeCallback(glfwFramebuferSizeHandler callback);