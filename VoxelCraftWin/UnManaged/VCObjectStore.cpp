//
//  VCObjectStore.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCObjectStore.h"

VCObjectStore* VCObjectStore::Instance;

VCObjectStore::VCObjectStore():
	m_length(1000),
	m_count(0)
{
    VCObjectStore::Instance = this;
}

VCObjectStore::~VCObjectStore()
{
    free(m_objectArray);
}

void VCObjectStore::Initalize()
{
	// Init size of 1K objects
	m_objectArray = (void**) malloc(sizeof(void*) * 1000);
    std::cout << "VCObjectStore Initialized." << std::endl;
}

int VCObjectStore::RegisterObject (void* obj)
{
    int keyId;
    
    if ( m_freedKeys.size() != 0 )
    {
        keyId = *m_freedKeys.begin();
        m_freedKeys.erase(m_freedKeys.begin());
    }
    
    else
    {
        keyId = m_count++;
        
        // Resize needed
        if ( m_count == m_length )
        {
            void** newArray = (void**) malloc(sizeof(void*) * m_length * 2);
            memcpy(newArray, m_objectArray, m_length * sizeof(void*));
            free(m_objectArray);
            m_objectArray = newArray;
            m_length *= 2;
        }
    }
    
    m_objectArray[keyId] = obj;
    return keyId;
}

void VCObjectStore::UpdatePointer(int id, void* obj)
{
    m_objectArray[id] = obj;
}

void* VCObjectStore::GetObject(int id)
{
    return m_objectArray[id];
}

void VCObjectStore::ReleaseObject (int id)
{
    m_freedKeys.insert(id);
}
