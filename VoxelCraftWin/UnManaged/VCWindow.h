//
//  VCWindow.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCWindow__
#define __VoxelCraftOSX__VCWindow__

#include "PCH.h"
#include "VCMonoMethod.h"

// Creates and manages a window and OpenGL context
class VCWindow
{
public:
    
    VCWindow();
    ~VCWindow();
    
    void Initalize();

	void SwapBuffers();
	void SetTitle(string title);
	void SetVSync(bool enabled);

public:
	static VCWindow* Instance;
	GLFWwindow* GLFWWindowHandle;
	Rectangle FullViewport;
	int Width;
	int Height;

private:
	VCMonoMethod* SizeChangeFunction;
    friend void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height);
	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
void VCInteropWindowSwapBuffers();
bool VCInteropWindowShouldClose();
void VCInteropWindowGetSize(int* width, int* height);

#endif /* defined(__VoxelCraftOSX__VCWindow__) */
