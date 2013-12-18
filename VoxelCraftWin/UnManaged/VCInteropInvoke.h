//
//  VCInteropInvoke.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "UnManagedInvokes.h"
#include "InvokeAPIList.h"

#define VC_INVOKE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) static RETURNTYPE FNAME ARGS

class VCInteropInvoke
{
public:

	VC_COLLAPSED_INVOKE_API

private:
	VCInteropInvoke(void){}
	~VCInteropInvoke(void){}
};

