//
//  ManagedInvokes.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//


#include "Stdafx.h"
#include "UnManagedInvokes.h"
#include "CLInvokes.h"

#include "InvokeAPIList.h"


#define VC_INVOKE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) RETURNTYPE NATIVE_INVOKE_##FNAME ARGS { return CLInvokes::##FNAME NAMESONLY;  }
VC_COLLAPSED_INVOKE_API