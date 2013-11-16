//
//  TexturePassThrough.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150
	
in vec3 position;
out vec2 UV;

void main()
{
	gl_Position =  vec4(position, 1);
	UV = (position.xy + vec2(1, 1)) / 2.0;
}