//
//  VCGLVertexBuffer.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/12/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLBuffer.h"

VCGLBuffer::VCGLBuffer(void):
	m_VAO(0),
	m_VBO(0),
	m_VIB(0),
	m_VBOSpec(NULL),
	m_vCount(0),
	m_iCount(0)
{
	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	ZERO_CHECK(m_VAO);
	glErrorCheck();
	
	m_VBOSpec = new VCGLVertexBufferAttributeSpec(this);

	VCLog::Info("VAO Created", "Resources");
}


VCGLBuffer::~VCGLBuffer(void)
{
	// Something is really fucked up... skip cleaning for now.
	return;

	delete m_VBOSpec;

	// Release VAO
	glDeleteVertexArrays(1, &m_VAO);
	
	// Conditionally release VBO, VIO
	if ( m_VBO ) 
		glDeleteBuffers(1, &m_VBO);

	if ( m_VIB ) 
		glDeleteBuffers(1, &m_VIB);

	VCLog::Info("VAO Released", "Resources");
}

void VCGLBuffer::Draw()
{
	glBindVertexArray(m_VAO);

	if ( m_VIB )
		// Draw Element List
		glDrawElements(m_primitivesType, m_iCount, m_indexBufferType, 0);

	else
		// Draw Vertex List
		glDrawArrays(m_primitivesType, 0, m_vCount);

}

VCGLVertexBufferAttributeSpec& VCGLBuffer::VertexBufferSpecification(VCGLDrawPrimitives::Types drawPrimitiveType /*= VCGLDrawPrimitives::Triangles*/ )
{
	glBindVertexArray(m_VAO);
	m_primitivesType = drawPrimitiveType;

	if( !m_VBO )
	{
		// Create VBO
		glGenBuffers(1, &m_VBO);
		ZERO_CHECK(m_VBO);
		glErrorCheck();
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	return *m_VBOSpec;
}

void VCGLBuffer::IndexBufferSpecification( int size, void* data, int count, VCGLDrawModes::Types drawMode /*= VCGLDrawModes::Static*/ )
{
	glBindVertexArray(m_VAO);
	m_indexBufferType = drawMode;
	m_iCount = count;

	if( !m_VIB )
	{
		// Create VBO
		glGenBuffers(1, &m_VIB);
		ZERO_CHECK(m_VIB);
		glErrorCheck();
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMode);
	glErrorCheck();
}

VCGLVertexBufferAttributeSpec::VCGLVertexBufferAttributeSpec(VCGLBuffer* coupledBuffer):
	m_coupledBuffer(coupledBuffer)
{
}

VCGLVertexBufferAttributeSpec::~VCGLVertexBufferAttributeSpec()
{
}

VCGLVertexBufferAttributeSpec& VCGLVertexBufferAttributeSpec::SetVertexData( UInt32 size, void* data, int count, VCGLDrawModes::Types drawMode /*= VCGLDrawModes::Static*/ )
{
	glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
	m_coupledBuffer->m_vCount = count;
	return *this;
}

VCGLVertexBufferAttributeSpec& VCGLVertexBufferAttributeSpec::SetVertexAttribute(VCShaderAttribute::AttributeTypes attribType, int count, VCGLPrimitives::Types primitiveType, bool normalize, int strideSize, size_t offset )
{
	glEnableVertexAttribArray(attribType);
	glVertexAttribPointer(attribType, count, (GLenum) primitiveType, normalize,	strideSize,	(void*) offset );
	return *this;
}

VCGLVertexBufferAttributeSpec& VCGLVertexBufferAttributeSpec::SetVertexAttributeI( VCShaderAttribute::AttributeTypes attribType, int count, VCGLPrimitives::Types primitiveType, int strideSize, size_t offset )
{
	glEnableVertexAttribArray(attribType);
	glVertexAttribIPointer(attribType, count, (GLenum) primitiveType, strideSize, (void*) offset );
	return *this;
}
