//
//  CallbackHost.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "CallbackHost.h"
#include "ManagedInvoke.h"

// Invoke the managed CLI register function.
void RegisterICallbacks()
{
	ManagedInvoke::RegisterICallbacks();
}
