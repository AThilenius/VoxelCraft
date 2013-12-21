//
//  Gui.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec3 Position;
in vec4 Color;

uniform mat4 projMatrix;

out vec4 VaryingColor;

void main()
{
	gl_Position =  projMatrix * vec4(Position, 1);
	VaryingColor =  Color;
}