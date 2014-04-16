//
//  VCGLMarshaledBuffer.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 4/15/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLMarshaledBuffer.h"
#include "VCObjectStore.h"
#include "VCGLBuffer.h"

VCGLMarshaledBuffer::VCGLMarshaledBuffer(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
	GLBuffer = new VCGLBuffer();
	BufferSpec = GLBuffer->m_VBOSpec;
}

VCGLMarshaledBuffer::~VCGLMarshaledBuffer(void)
{
	delete GLBuffer;
}

int VCInteropGLBufferCreate()
{
	return (new VCGLMarshaledBuffer())->Handle;
}

void VCInteropGLBufferRelease(int handle)
{
	delete (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
}

void VCInteropGLBufferDraw(int handle)
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->GLBuffer->Draw();
}

void VCInteropVCGLBufferSetDrawPrimitiveType(int handle, int drawPrimitiveTypeOffset)
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->GLBuffer->VertexBufferSpecification((VCGLDrawPrimitives::Types) VCGLDrawPrimitives::RuntimeLookupTable[drawPrimitiveTypeOffset]);
}

void VCInteropVCGLBufferSetVertexData( int handle, UInt32 size, void* data, int count, int drawMode )
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->BufferSpec->SetVertexData(size, data, count, (VCGLDrawModes::Types) VCGLDrawModes::RuntimeLookupTable[drawMode]);
}

void VCInteropVCGLBufferSetVertexAttribute(int handle, 
										   VCShaderAttribute::AttributeTypes attribType, 
										   int count, 
										   int primitivesType, 
										   bool normalize, 
										   int strideSize, 
										   size_t offset)
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->BufferSpec->SetVertexAttribute(attribType, count, (VCGLPrimitives::Types) VCGLPrimitives::RuntimeLookupTable[primitivesType], normalize, strideSize, offset);
}

void VCInteropVCGLBufferSetVertexAttributeI(int handle, 
											VCShaderAttribute::AttributeTypes attribType, 
											int count, 
											int primitivesType, 
											int strideSize, 
											size_t offset)
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->BufferSpec->SetVertexAttributeI(attribType, count, (VCGLPrimitives::Types) VCGLPrimitives::RuntimeLookupTable[primitivesType], strideSize, offset);
}

void VCInteropVCGLBUfferSetIndexBuffer(int handle, 
									   int size, 
									   void* data, 
									   int count, 
									   int primitivesType_indecieType, 
									   int drawMode)
{
	VCGLMarshaledBuffer* obj = (VCGLMarshaledBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->GLBuffer->IndexBufferSpecification(size, data, count, (VCGLPrimitives::Types) VCGLPrimitives::RuntimeLookupTable[primitivesType_indecieType], (VCGLDrawModes::Types) VCGLDrawModes::RuntimeLookupTable[drawMode]);
}