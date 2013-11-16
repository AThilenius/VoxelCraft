//
//  Terrain.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 position;
in vec3 color;
in int flags;

out VSOutput
{
	vec3 color;
	int flags;
} vs_out;

void main()
{
	gl_Position =  position;
	vs_out.color = color;
	vs_out.flags = flags;
}