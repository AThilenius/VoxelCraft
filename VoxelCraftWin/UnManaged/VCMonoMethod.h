//
//  VCMonoMethod.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/4/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

class VCMonoMethod
{
public:
	VCMonoMethod(MonoMethod* method):
		InternalMethod(method){}
	~VCMonoMethod(void);

	void Invoke (void ** args)
	{
		mono_runtime_invoke(InternalMethod, NULL, args, NULL);
	}

	MonoMethod* InternalMethod;
};

