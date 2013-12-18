//
//  ManagedInvoke.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

using namespace VCEngine;

#include "CallbackHost.h"
#include "CallbackAPIList.h"

#define VC_EXPOSE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) virtual RETURNTYPE Invoke##FNAME ARGS { return CallbackHost##FNAME NAMESONLY; }

ref class ManagedInvoke : VCEngine::IInteropOutCallbacks
{
public:
	ManagedInvoke(void){}
	static void RegisterICallbacks() { VCEngine::InteropOut::SetCallbacks(gcnew ManagedInvoke()); }

	VC_COLLAPSED_EXPOSE_API
};