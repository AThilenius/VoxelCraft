//
//  ColorPassThrough.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 ColorVarying;
out vec4 FragColor;

void main()
{
	FragColor = vec4(1, 0, 0, 1);
	//FragColor = ColorVarying;
}