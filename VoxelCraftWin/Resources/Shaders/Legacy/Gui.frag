//
//  Gui.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 VaryingColor;

uniform float NoiseScaler;

out vec4 fragColor;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	fragColor = VaryingColor;
	fragColor.xyz = fragColor.xyz - (vec3(1, 1, 1) * rand(gl_FragCoord.xy) * NoiseScaler);
}