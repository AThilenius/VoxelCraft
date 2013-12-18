//
//  CallbackHost.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "CallbackAPIList.h"

#define VC_EXPOSE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) typedef RETURNTYPE(*VCInteropType##FNAME) ARGS; __declspec(selectany) VCInteropType##FNAME CallbackHost##FNAME = 0;

void RegisterICallbacks();
VC_COLLAPSED_EXPOSE_API