//
//  VoxelFallback.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/29/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec4 colorVarying;

out vec4 color;

void main()
{
	vec3 n = normalize( Normal_cameraspace );
	vec3 l = normalize( LightDirection_cameraspace );
	float cosTheta = clamp( dot( n,l ), 0, 1 );

	color = 
	colorVarying * 0.6 +
	colorVarying * cosTheta * 0.3;

	color.w = colorVarying.w;
}