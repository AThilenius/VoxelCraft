//
//  VCSparseVoxelOctree.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCSvoNode;
class VCBlock;

class VCSparseVoxelOctree
{
public:
	~VCSparseVoxelOctree(void);

	VCSparseVoxelOctree* CreateFromChunkBuffer(VCBlock* blocks, int width);

private:
	VCSparseVoxelOctree(void);
	int GetRunDepth (int width);

public:
	VCSvoNode* Head;
	int RunDepth;
};

