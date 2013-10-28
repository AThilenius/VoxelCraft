//
//  VCObjectStore.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include <set>

class VCObjectStore
{
public:
    VCObjectStore();
    ~VCObjectStore();
    
    void Initalize();
    
    int RegisterObject (void* obj);
    void UpdatePointer(int id, void* obj);
    void* GetObject (int id);
    void ReleaseObject (int id);
    
public:
    static VCObjectStore* Instance;
    
private:
    void** m_objectArray;
    std::set<int> m_freedKeys;
    
    int m_length, m_count;
};