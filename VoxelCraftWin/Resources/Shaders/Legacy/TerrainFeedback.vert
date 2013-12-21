//
//  TerrainFeedback.vert
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/19/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

// From Transform Feedback Buffer
in vec4 positionIn;
//in vec3 normalIn;
//in vec3 colorIn;

// To Fragment Shader
//out vec3 normalOut;
//out vec3 colorOut;

uniform mat4 MVP;

void main()
{
	gl_Position = /* MVP * */ positionIn;
	//normalOut = normalIn;
	//colorOut = colorIn;
}
