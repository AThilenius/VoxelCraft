//
//  TexturePassThrough.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec2 UV;
out vec4 color;
uniform sampler2D texture;

void main()
{
	color = texture2D(texture, UV);
}