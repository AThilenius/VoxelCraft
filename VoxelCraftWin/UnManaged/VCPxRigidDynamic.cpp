//
//  VCPxRigidDynamic.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxRigidDynamic.h"

#include "VCObjectStore.h"
#include "VCPxPhysics.h"


VCPxRigidDynamic::VCPxRigidDynamic(VCFloat3 pos, VCFloat4 rot)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxRigidDynamic::~VCPxRigidDynamic(void)
{
}
