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
	m_VBOSpec(NULL)
{
	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	ZERO_CHECK(m_VAO);
	glErrorCheck();
	
	m_VBOSpec = new VCGLVertexBufferAttributeSpec();

	std::cout << "VAO Created" << std::endl;
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

	std::cout << "VAO Released" << std::endl;
}

void VCGLBuffer::Bind()
{
	glBindVertexArray(m_VAO);
}

VCGLVertexBufferAttributeSpec& VCGLBuffer::VertexBufferSpecification()
{
	glBindVertexArray(m_VAO);

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

void VCGLBuffer::IndexBufferSpecification( int size, void* data, VCGLDrawModes::Types drawMode /*= VCGLDrawModes::Static*/ )
{
	glBindVertexArray(m_VAO);

	if( !m_VIB )
	{
		// Create VBO
		glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_VIB);
		ZERO_CHECK(m_VIB);
		glErrorCheck();
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMode);
}

VCGLVertexBufferAttributeSpec::VCGLVertexBufferAttributeSpec()
{
}

VCGLVertexBufferAttributeSpec::~VCGLVertexBufferAttributeSpec()
{
}

VCGLVertexBufferAttributeSpec& VCGLVertexBufferAttributeSpec::SetVertexData( UInt32 size, void* data, VCGLDrawModes::Types drawMode /*= VCGLDrawModes::Static*/ )
{
	glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
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
