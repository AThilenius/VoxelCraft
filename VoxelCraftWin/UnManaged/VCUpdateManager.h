//
//  VCUpdateManager.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __VoxelCraftOSX__VCUpdateManager__
#define __VoxelCraftOSX__VCUpdateManager__

#include "PCH.h"

typedef void (*noArgCallback) ();

class VCUpdateManager
{
public:
    VCUpdateManager();
    ~VCUpdateManager();
    
    void Update();
    
    
public:
    static VCUpdateManager* Instance;
    
private:
    //noArgCallback m_updateHandler;
    
    // ================================      Interop      ============
public:
    int Handle;
    static void RegisterMonoHandlers();
    
private:
    friend void VCInteropRegisterUpdateHandler(noArgCallback* callback);
};

void VCInteropRegisterUpdateHandler(noArgCallback* callback);


#endif /* defined(__VoxelCraftOSX__VCUpdateManager__) */
