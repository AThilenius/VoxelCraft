//
//  VCMonoMethod.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/4/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMonoMethod.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

VCMonoMethod::VCMonoMethod( MonoMethod* method ) :
	InternalMethod(method)
{

}

VCMonoMethod::~VCMonoMethod()
{

}

void VCMonoMethod::Invoke( void ** args )
{
	mono_runtime_invoke(InternalMethod, NULL, args, NULL);
}
