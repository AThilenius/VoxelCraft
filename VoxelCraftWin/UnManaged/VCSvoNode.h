//
//  VCSvoNode.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

//  Node:
//  0               32               64
//  |---------------------------------| - ( + 0 )
//  | ChildBlock* 1  |  Color RGBA    | 
//  |---------------------------------| - ( + 8 )

#pragma once

class VCSvoNodeBlock;

class VCSvoNode
{
public:
	VCSvoNode(void);
	~VCSvoNode(void);

	VCSvoNodeBlock* Child;
	GLubyte4 Color;
};