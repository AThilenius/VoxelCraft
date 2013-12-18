//
//  VCInteropExpose.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "CallbackHost.h"
#include "CallbackAPIList.h"

#define VC_EXPOSE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) typedef RETURNTYPE(*VCInteropType##FNAME) ARGS; static void FNAME (VCInteropType##FNAME p){CallbackHost##FNAME=p;}

class VCInteropExpose
{
public:
	VC_COLLAPSED_EXPOSE_API

private:
	VCInteropExpose(void){}
	~VCInteropExpose(void){}
};