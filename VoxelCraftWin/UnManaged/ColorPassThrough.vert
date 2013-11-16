//
//  ColorPassThrough.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 Position;
in vec4 Color;

uniform mat4 MVP;

out vec4 ColorVarying;

void main()
{
	gl_Position =  MVP * Position;
	ColorVarying = Color;
}