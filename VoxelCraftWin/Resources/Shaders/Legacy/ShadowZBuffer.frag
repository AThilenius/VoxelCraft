//
//  ShadowZBuffer.frag
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

out float fragmentdepth;

void main()
{
	fragmentdepth = gl_FragCoord.z;
}