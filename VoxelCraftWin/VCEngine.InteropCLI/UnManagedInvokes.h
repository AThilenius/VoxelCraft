//
//  ManagedInvokes.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "InvokeAPIList.h"

#ifdef DLL_EXPORT
#define DLLAPI  __declspec(dllexport)
#else
#define DLLAPI  __declspec(dllimport)
#endif

#define VC_INVOKE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) DLLAPI RETURNTYPE NATIVE_INVOKE_##FNAME ARGS
VC_COLLAPSED_INVOKE_API