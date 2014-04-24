//
//  AssimpBindings.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 4/23/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "VCMesh.h"

DLL_EXPORT_API void* VCIneteropAssimpLoadScene(char* fullPath, int loadFlags, int* meshCount);
DLL_EXPORT_API void VCInteropAssimpGetMeshMeta(void* scene, int meshId, int* vertCount, int* facesCount, int* animMeshesCount, int* bonesCount);

/// Important note: 'indexBuffer' must be a UInt8*, UInt16* or UInt32* buffer, depending on the smallest size that will fit the index count.
DLL_EXPORT_API void VCInteropAssimpGetMeshData(void* scene, int meshId, VCStandardVerticie* vertBufferRef, void* indexBuffer);
DLL_EXPORT_API void VCInteropAssimpFreeScene(void* scene);