//
//  VoxelFallback.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/29/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 position;
in int normal;
in vec4 color;

out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out vec4 colorVarying;

uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 LightInvDirection_worldspace;
uniform vec3 NormalLookupTable[6] = vec3[6] (
	vec3(-1.0, 0.0, 0.0),
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, -1.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, -1.0),
	vec3(0.0, 0.0, 1.0)
);

void main()
{
	vec3 vertexNormal_modelspace = NormalLookupTable[int(normal)];
	
	gl_Position =  MVP * position;
	colorVarying = color;
	LightDirection_cameraspace = ( ViewMatrix * vec4( LightInvDirection_worldspace, 0 ) ).xyz;
	Normal_cameraspace = ( ViewMatrix * ModelMatrix * vec4( vertexNormal_modelspace, 0 ) ).xyz;
}