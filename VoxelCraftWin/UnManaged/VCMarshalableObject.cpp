//
//  MarshalableObject.cpp
//  Engine
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCMarshalableObject.h"

VCMarshalableObject::VCMarshalableObject():
    Handle(-1)
{
    Handle = VCObjectStore::Instance->RegisterObject(this);
}

VCMarshalableObject::~VCMarshalableObject()
{
    if ( Handle == -1 )
        return;
    
    VCObjectStore::Instance->ReleaseObject(Handle);
    Handle = -1;
}