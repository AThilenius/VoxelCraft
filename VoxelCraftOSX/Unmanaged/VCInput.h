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
    void Update();
    
    static bool IsKeyDown ( int keycode );
    
    static void GetMouse ( float* x, float* y );
    static bool IsMouseDown ( int buttonID );
    
    static glm::vec2 GetMouse2 ( );
    static glm::vec3 GetMouse3 ( );
    static glm::vec3 GetStrafe ( );
    
    static VCInput* Instance;
    
private:
    bool m_keysDown[325];
    bool m_mouseButtonsDown[10];
    float m_deltaX, m_deltaY;
    
    friend void GLFWCALL KeyHanlder( int key, int action );
    friend void GLFWCALL MouseMoveHandler( int x, int y );
    friend void GLFWCALL MouseButtonHanlder( int button, int action );
};

#endif /* defined(__VoxelCraftOSX__VCInputPreProcessor__) */
