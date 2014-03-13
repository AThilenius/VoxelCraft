//
//  VCWindow.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCMonoMethod;
struct GLFWwindow;


// Creates and manages a window and OpenGL context
class VCWindow
{
public:
    
    VCWindow();
    ~VCWindow();
    
    void Initalize();

	void SwapBuffers();
	void PollEvents();
	void SetTitle(std::string title);
	void SetVSync(bool enabled);

public:
	static VCWindow* Instance;
	GLFWwindow* GLFWWindowHandle;
	VCRectangle FullViewport;
	int Width;
	int Height;

private:
	VCMonoMethod* SizeChangeFunction;
    friend void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height);
};

// Interop
DLL_EXPORT_API void VCInteropWindowSwapBuffers();
DLL_EXPORT_API void VCInteropWindowPollEvents();
DLL_EXPORT_API bool VCInteropWindowShouldClose();
DLL_EXPORT_API void VCInteropWindowVSync(int enabled); 
DLL_EXPORT_API void VCInteropWindowGetSize(int* width, int* height);
DLL_EXPORT_API void VCInteropWindowSetSize(int width, int height);
DLL_EXPORT_API void VCInteropWindowGetPos(int* x, int* y);
DLL_EXPORT_API void VCInteropWindowSetPos(int x, int y);
DLL_EXPORT_API void VCInteropGetMonitorSize( int* width, int* height );

typedef void (*glfwFramebuferSize)(int, int);
DLL_EXPORT_API void VCInteropRegisterResizeCallback(glfwFramebuferSize callback);