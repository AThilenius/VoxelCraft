//
//  VCCamera.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCCamera.h"
#import "VCSceneGraph.h"


VCCamera::VCCamera(void)
{
    int width, height;
    glfwGetWindowSize(&width, &height);
    Frame = Rectangle(0, 0, width, height);
    
    VCSceneGraph::Instance->RegisterCamera(this);
}


VCCamera::~VCCamera(void)
{
}

void VCCamera::PreRender()
{
    glViewport(Frame.X, Frame.Y, Frame.Width, Frame.Height);
    
	ProjectionMatrix = glm::perspective(65.0f, 4.0f / 3.0f, 0.1f, 400.0f);

    // Ensure that the Transform's model matrix is alreay build
    Transform->PreRender();
    ViewMatrix = Transform->ModelMatrix;

	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
}
