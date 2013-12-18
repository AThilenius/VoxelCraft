//
//  VCInteropInvoke.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "UnManagedInvokes.h"

#define VC_USE_CLI 1

#define VC_CLI_INVOKE_API_0(methodName) methodName() { return UnManagedInvokes::methodName();  }
#define VC_CLI_INVOKE_API_1(methodName,T,name) methodName(T name) { return UnManagedInvokes::methodName(name);  }
#define VC_CLI_INVOKE_API_2(methodName,T,name,T2,name2) methodName(T name, T2 name2) { return UnManagedInvokes::methodName(name, name2);  }

class VCInteropInvoke
{
public:
	VCInteropInvoke(void);
	~VCInteropInvoke(void);

	// =====   Managed Functions   ======================================================

#ifdef VC_USE_CLI

	void VC_CLI_INVOKE_API_0(EditorEntry);

#endif

	// ==================================================================================
};

