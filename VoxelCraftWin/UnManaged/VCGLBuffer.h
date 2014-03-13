//
//  VCGLVertexBuffer.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/12/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCShadeTypes.h"
#include "VCGLTypes.h"

// Forwards
class VCGLVertexBufferAttributeSpec;

/************************************************************************/
/* Holds a single VAO and 0-1 Vertex / Index Buffers                    */
/************************************************************************/
class VCGLBuffer
{
public:
	VCGLBuffer();
	~VCGLBuffer();

	/// Binds the VAO only.
	void Bind();

	/// Access point for all vertex attribute buffer specification
	VCGLVertexBufferAttributeSpec& VertexBufferSpecification();

	/// Direct Index buffer setup
	void IndexBufferSpecification(int size, void* data, VCGLDrawModes::Types drawMode = VCGLDrawModes::Static);


private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_VIB;

	VCGLVertexBufferAttributeSpec* m_VBOSpec;
	
private:
	friend class VCGLVertexBufferAttributeSpec;
	DISALLOW_COPY_AND_ASSIGN(VCGLBuffer);
};

/************************************************************************/
/* Fluent API chain for vertex buffer attribute specification           */
/************************************************************************/
class VCGLVertexBufferAttributeSpec
{
public:
	~VCGLVertexBufferAttributeSpec();
	
	/// Malloc / Memcpy to GPU memory
	VCGLVertexBufferAttributeSpec& SetVertexData(UInt32 size, void* data, VCGLDrawModes::Types drawMode = VCGLDrawModes::Static);

	/// Specify a non-integral type attribute ( floating point based )
	VCGLVertexBufferAttributeSpec& SetVertexAttribute(VCShaderAttribute::AttributeTypes attribType, int count, VCGLPrimitives::Types primitiveType, bool normalize, int strideSize, size_t offset );

	/// Specify an integral type attribute ( Integer based )
	VCGLVertexBufferAttributeSpec& SetVertexAttributeI(VCShaderAttribute::AttributeTypes attribType, int count, VCGLPrimitives::Types primitiveType, int strideSize, size_t offset );

private:
	VCGLVertexBufferAttributeSpec();

private:
	VCGLBuffer* m_coupledBuffer;

private:
	friend class VCGLBuffer;
	DISALLOW_COPY_AND_ASSIGN(VCGLVertexBufferAttributeSpec);
};