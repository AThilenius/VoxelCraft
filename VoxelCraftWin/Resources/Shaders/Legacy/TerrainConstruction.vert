//
//  TerrainConstruction.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

// From VBO
in vec3 positionIn;
in vec3 colorIn;
in int flagsIn;

// To Geometry Shader
out vec3 colorOut;
out int flagsOut;

void main()
{
	gl_Position =  vec4(positionIn, 1);
	colorOut = colorIn;
	flagsOut = flagsIn;
}