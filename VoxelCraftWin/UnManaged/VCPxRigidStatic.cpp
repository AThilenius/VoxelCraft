//
//  VCPxRigidStatic.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxRigidStatic.h"

#include "VCObjectStore.h"


VCPxRigidStatic::VCPxRigidStatic(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxRigidStatic::~VCPxRigidStatic(void)
{
}
