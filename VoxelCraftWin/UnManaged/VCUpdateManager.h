//
//  VCUpdateManager.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/31/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

typedef void (*noArgCallback) ();

class VCUpdateManager
{
public:
    VCUpdateManager();
    ~VCUpdateManager();
    
    void Update();
    
    
public:
    static VCUpdateManager* Instance;
        
    // ================================      Interop      ============
public:
    int Handle;
    
private:
    friend void VCInteropRegisterUpdateHandler(noArgCallback* callback);
};

//DLL_EXPORT_API void VCInteropRegisterUpdateHandler(noArgCallback* callback);