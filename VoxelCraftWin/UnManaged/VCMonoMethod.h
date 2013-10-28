//
//  VCMonoMethod.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/4/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct _MonoMethod;
typedef struct _MonoMethod MonoMethod;

class VCMonoMethod
{
public:
	VCMonoMethod(MonoMethod* method);
	~VCMonoMethod(void);

	void Invoke (void ** args);

	MonoMethod* InternalMethod;
};

