//
//  VCInputPreProcessor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCInputPreProcessor__
#define __VoxelCraftOSX__VCInputPreProcessor__

#import "PCH.h"

class VCInput
{
public:
    VCInput();
    ~VCInput();
    
    void Initalize();
    
    static bool IsKeyDown ( int keycode );
    static void GetMouseLocation ( int* x, int* y );
    static bool IsMouseDown ( int buttonID );
    
    static VCInput* Instance;
    
private:
    bool m_keysDown[325];
    bool m_mouseButtonsDown[10];
    int m_mouseX;
    int m_mouseY;
    
    friend void GLFWCALL KeyHanlder( int key, int action );
    friend void GLFWCALL MouseMoveHandler( int x, int y );
    friend void GLFWCALL MouseButtonHanlder( int button, int action );
};

#endif /* defined(__VoxelCraftOSX__VCInputPreProcessor__) */
