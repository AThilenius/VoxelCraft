//
//  VCSvoLeafBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

//  Leaf Block:
//  0               32
//  |----------------| - ( + 0 )
//  |  Color RGBA    | 
//  |----------------| - ( + 4 )
//  |  Color RGBA    | 
//  |----------------| - ( + 8 )
//  |  Color RGBA    | 
//  |----------------| - ( + 12 )
//  |  Color RGBA    | 
//  |----------------| - ( + 16 )
//  |  Color RGBA    | 
//  |----------------| - ( + 20 )
//  |  Color RGBA    | 
//  |----------------| - ( + 24 )
//  |  Color RGBA    | 
//  |----------------| - ( + 28 )
//  |  Color RGBA    | 
//  |----------------| - ( + 32 )

#pragma once


class VCSvoLeafBlock
{
public:
	VCSvoLeafBlock(void);
	~VCSvoLeafBlock(void);
};

