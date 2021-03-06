//
//  ShadowZBuffer.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 vertexPosition_modelspace;
uniform mat4 depthMVP;

void main()
{
	gl_Position =  depthMVP * vertexPosition_modelspace;
}