//
//  VCGameObject.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMarshaledGameObject.h"

#include "VCObjectStore.h"

DLL_EXPORT_API void VCInteropGameObjectSetModelMatrix( int handle, glm::mat4 matrix )
{
	VCMarshaledGameObject* obj = (VCMarshaledGameObject*) VCObjectStore::Instance->GetObject(handle);
	obj->ModelMatrix = matrix;
}