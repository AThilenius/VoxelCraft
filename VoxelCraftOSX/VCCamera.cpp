//
//  VCCamera.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCCamera.h"


VCCamera::VCCamera(void)
{
    m_position = vec3(0.0f, 0.0f, -100.0f);
}


VCCamera::~VCCamera(void)
{
}

void VCCamera::PreRender()
{
	ProjectionMatrix = glm::perspective(65.0f, 4.0f / 3.0f, 0.1f, 400.0f);
    
    
//    float deltaRotY = self.InputProcessor.RightJoystick.Strafe;
//    float deltaRotX = self.InputProcessor.RightJoystick.Forward;
//    
//    m_rot.x += deltaRotX * 0.05;
//    m_rot.y += deltaRotY * 0.075;
//    
//    float deltaTransX = sinf(m_rot.y) * self.InputProcessor.Joystick.Forward * MAX_MOVEMENT_SPEED;
//    float deltaTransY = -sinf(m_rot.x) * self.InputProcessor.Joystick.Forward * MAX_MOVEMENT_SPEED;
//    float deltaTransZ = cosf(m_rot.y) * self.InputProcessor.Joystick.Forward * MAX_MOVEMENT_SPEED;
//    
//    if ( m_rot.x > 90.0f * 0.0174532925 )
//        m_rot.x = 90.0f * 0.0174532925;
//    
//    if ( m_rot.x < -90.0f * 0.0174532925 )
//        m_rot.x = -90.0f * 0.0174532925;
//    
//    m_pos.x += deltaTransX;
//    m_pos.y += deltaTransY;
//    m_pos.z += deltaTransZ;
//    
//    GLKMatrix4 trans = GLKMatrix4Identity;
//    trans = GLKMatrix4RotateX(trans, -m_rot.x);
//    trans = GLKMatrix4RotateY(trans, -m_rot.y);
//    trans = GLKMatrix4Translate(trans, m_pos.x, m_pos.y, m_pos.z);
//    
//    m_effect.transform.modelviewMatrix = trans;
    
    
    glm::vec3 deltaRot = VCInput::GetMouse3();
    glm::vec3 deltaStrafe = VCInput::GetStrafe();
    
    m_rotation += deltaRot * 20.0f;
    
    float deltaTransX = sinf(m_rotation.y) * deltaStrafe.z;
    float deltaTransY = -sinf(m_rotation.x) * deltaStrafe.z;
    float deltaTransZ = cosf(m_rotation.y) * deltaStrafe.z;
    
//    if ( m_rotation.x > 90.0f * 0.0174532925 )
//        m_rotation.x = 90.0f * 0.0174532925;
//    
//    if ( m_rotation.x < -90.0f * 0.0174532925 )
//        m_rotation.x = -90.0f * 0.0174532925;
    
    m_position.x += deltaTransX;
    m_position.y += deltaTransY;
    m_position.z += deltaTransZ;
    
    
//    GLKMatrix4 trans = GLKMatrix4Identity;
//    trans = GLKMatrix4RotateX(trans, -m_rot.x);
//    trans = GLKMatrix4RotateY(trans, -m_rot.y);
//    trans = GLKMatrix4Translate(trans, m_pos.x, m_pos.y, m_pos.z);
    
    ViewMatrix = glm::mat4();
    ViewMatrix = glm::rotate(ViewMatrix, m_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    ViewMatrix = glm::rotate(ViewMatrix, -m_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    //ViewMatrix = glm::rot
	ViewMatrix = glm::translate(ViewMatrix, m_position);

	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
}
