//
//  Terrain.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in GSOutput
{
	vec3 color;
	vec3 normal;
} gs_out;

out vec4 color;

uniform vec3 LightDir;
	
void main()
{
	vec3 l = normalize( LightDir );
	float cosTheta = clamp( dot(gs_out.normal, l), 0, 1 );

	color.xyz = 
		gs_out.color * 0.6 +
		gs_out.color * cosTheta * 0.3;
	color.w = 1;
}