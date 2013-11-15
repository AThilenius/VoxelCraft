//
//  VCSvoNodeBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

//  NodeBlock:
//  0               32               64
//  |---------------------------------| - ( + 0 )
//  | ChildBlock* 1  |  Color RGBA    | 
//  |---------------------------------| - ( + 8 )
//  | ChildBlock* 2  |  Color RGBA    | 
//  |---------------------------------| - ( + 16 )
//  | ChildBlock* 3  |  Color RGBA    | 
//  |---------------------------------| - ( + 24 )
//  | ChildBlock* 4  |  Color RGBA    | 
//  |---------------------------------| - ( + 32 )
//  | ChildBlock* 5  |  Color RGBA    | 
//  |---------------------------------| - ( + 40 )
//  | ChildBlock* 6  |  Color RGBA    | 
//  |---------------------------------| - ( + 48 )
//  | ChildBlock* 7  |  Color RGBA    | 
//  |---------------------------------| - ( + 56 )
//  | ChildBlock* 8  |  Color RGBA    | 
//  |---------------------------------| - ( + 64 )

#pragma once

#include "VCSvoNode.h"

class VCSvoNodeBlock
{
public:
	VCSvoNodeBlock(void);
	~VCSvoNodeBlock(void);

	VCSvoNode Children[8];
};

