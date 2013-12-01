//
//  TexturePassThrough.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec2 VaryingUV;

uniform sampler2D texture;

out vec4 fragColor;

void main()
{
	fragColor = texture2D(texture, VaryingUV);
}