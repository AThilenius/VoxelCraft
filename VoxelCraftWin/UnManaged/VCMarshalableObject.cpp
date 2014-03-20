//
//  MarshalableObject.cpp
//  Engine
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMarshalableObject.h"
#include "VCObjectStore.h"

VCMarshalableObject::VCMarshalableObject():
    Handle(-1)
{
	if (VCObjectStore::Instance == NULL)
	{
		VCObjectStore::Instance = new VCObjectStore();
		VCObjectStore::Instance->Initalize();
	}

    Handle = VCObjectStore::Instance->RegisterObject(this);
}

VCMarshalableObject::~VCMarshalableObject()
{
    if ( Handle == -1 )
        return;
    
    VCObjectStore::Instance->ReleaseObject(Handle);
    Handle = -1;
}