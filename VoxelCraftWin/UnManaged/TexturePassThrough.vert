//
//  TexturePassThrough.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150
	
in vec4 Position;
in vec2 UV;

uniform mat4 projMatrix;

out vec2 VaryingUV;

void main()
{
	gl_Position =  projMatrix * Position;
	VaryingUV =  UV;
}