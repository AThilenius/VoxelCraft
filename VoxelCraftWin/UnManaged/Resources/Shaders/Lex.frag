//
//  Lex.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec2 VaryingUV;
in vec4 VaryingColor;

uniform sampler2D glyphs;

out vec4 fragColor;

void main()
{
	vec4 tcolor = texture2D(glyphs, VaryingUV);
	float alpha = 1.0 - (tcolor.x );
	fragColor.xyz = VaryingColor.xyz;
	fragColor.w = alpha;
}