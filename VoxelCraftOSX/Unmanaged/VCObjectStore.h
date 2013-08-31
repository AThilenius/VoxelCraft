//
//  VCObjectStore.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCObjectStore__
#define __VoxelCraftOSX__VCObjectStore__

#import "PCH.h"

class VCObjectStore
{
public:
    VCObjectStore();
    ~VCObjectStore();
    
    int RegisterObject (void* obj);
    void* GetObject (int id);
    void ReleaseObject (int id);
    
public:
    static VCObjectStore* Instance;
    
private:
    void** m_objectArray;
    std::set<int> m_freedKeys;
    
    int m_length, m_count;
};

#endif /* defined(__VoxelCraftOSX__VCObjectStore__) */
