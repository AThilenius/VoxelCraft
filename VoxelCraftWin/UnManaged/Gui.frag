//
//  Gui.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

in vec4 VaryingColor;

out vec4 fragColor;

void main()
{
	fragColor = VaryingColor;
}