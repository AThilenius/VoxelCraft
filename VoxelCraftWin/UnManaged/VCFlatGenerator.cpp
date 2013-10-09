//
//  VCFlatGenerator.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/8/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCFlatGenerator.h"


void VCFlatGenerator::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.FlatChunkGenerator::VCInteropNewFlatGenerator",		(void*)VCInteropNewFlatGenerator);
	mono_add_internal_call("VCEngine.FlatChunkGenerator::VCInteropReleaseFlatGenerator",	(void*)VCInteropReleaseFlatGenerator);
}

int VCInteropNewFlatGenerator()
{
	VCFlatGenerator* ng = new VCFlatGenerator();
	return ng->Handle;
}

void VCInteropReleaseFlatGenerator( int handle )
{
	VCFlatGenerator* obj = (VCFlatGenerator*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}