//
//  VCInteropInvoke.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCInteropInvoke.h"

#define VC_INVOKE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) RETURNTYPE VCInteropInvoke::##FNAME ARGS { return NATIVE_INVOKE_##FNAME NAMESONLY;  }

VC_COLLAPSED_INVOKE_API