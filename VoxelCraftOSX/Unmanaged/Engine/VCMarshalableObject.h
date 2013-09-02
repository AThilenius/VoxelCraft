//
//  MarshalableObject.h
//  Engine
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __Engine__MarshalableObject__
#define __Engine__MarshalableObject__

#import "PCH.h"
#import "VCObjectStore.h"

class VCMarshalableObject
{
public:
    VCMarshalableObject();
    ~VCMarshalableObject();
    
    int Handle;
};

#endif /* defined(__Engine__MarshalableObject__) */