//
//  VCMonoMethod.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/4/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMonoMethod.h"

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
