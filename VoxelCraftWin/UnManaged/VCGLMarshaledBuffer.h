//
//  VCGLMarshaledBuffer.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 4/15/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// Forwards
class VCGLBuffer;
class VCGLVertexBufferAttributeSpec;

#include "VCMarshalableObject.h"
#include "VCShadeTypes.h"

/************************************************************************/
/* A marshaled facade of a VCGLBuffer for managed code. This class      */
/* should not be used by unmanaged code                                 */
/************************************************************************/
class VCGLMarshaledBuffer : public VCMarshalableObject
{
public:
	VCGLMarshaledBuffer();
	~VCGLMarshaledBuffer();

public:
	static int* VCGLPrimitivesLookupTable;
	static int* GLDrawModesLookupTable;

	VCGLBuffer* GLBuffer;
	VCGLVertexBufferAttributeSpec* BufferSpec;
};

DLL_EXPORT_API int VCInteropGLBufferCreate();
DLL_EXPORT_API void VCInteropGLBufferRelease(int handle);
DLL_EXPORT_API void VCInteropGLBufferDraw(int handle);
DLL_EXPORT_API void VCInteropVCGLBufferSetDrawPrimitiveType(int handle, int drawPrimitiveTypeOffset);
DLL_EXPORT_API void VCInteropVCGLBufferSetVertexData(int handle, UInt32 size, void* data, int count, int drawMode);
DLL_EXPORT_API void VCInteropVCGLBufferSetVertexAttribute(int handle, 
														  VCShaderAttribute::AttributeTypes attribType, 
														  int count, 
														  int primitivesType, 
														  bool normalize, 
														  int strideSize, 
														  size_t offset);
DLL_EXPORT_API void VCInteropVCGLBufferSetVertexAttributeI(int handle, 
														   VCShaderAttribute::AttributeTypes attribType, 
														   int count, 
														   int primitivesType, 
														   int strideSize, 
														   size_t offset);
DLL_EXPORT_API void VCInteropVCGLBUfferSetIndexBuffer(int handle, 
													  int size, 
													  void* data, 
													  int count, 
													  int primitivesType_indecieType, 
													  int drawMode);