//
//  TerrainFeedback.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/19/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

// From Vertex Shader
//in vec3 normalIn;
//in vec3 colorIn;

// To Screen
out vec4 Color;

//uniform vec3 LightDir;

void main()
{
	//float cosTheta = clamp( dot(normalIn, LightDir), 0, 1 );

	Color = vec4(1, 0, 0, 1);
	//Color.xyz = 
	//	colorIn * 0.6 +
	//	colorIn * cosTheta * 0.3;
	//Color.w = 1;
}