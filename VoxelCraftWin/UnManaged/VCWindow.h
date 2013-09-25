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
	int Width;
	int Height;
    
};

#endif /* defined(__VoxelCraftOSX__VCWindow__) */
