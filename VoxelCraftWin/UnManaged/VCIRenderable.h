//
//  VCIRenderable.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/28/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCIRenderable
{
public:
	virtual ~VCIRenderable() {}
	virtual void Render() = 0;
};
