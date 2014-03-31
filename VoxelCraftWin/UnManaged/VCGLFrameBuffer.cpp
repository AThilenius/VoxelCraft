//
//  VCGLFrameBuffer.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/26/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLFrameBuffer.h"
#include "VCGLTexture.h"
#include "VCObjectStore.h"

VCGLFrameBuffer* VCGLFrameBuffer::m_boundFrameBuffer = NULL;
VCGLFrameBuffer* VCGLFrameBuffer::m_defaultFrameBuffer = NULL;
VCGLFrameBuffer* VCGLFrameBuffer::m_textureTargetFrameBuffer = NULL;

VCGLFrameBuffer::VCGLFrameBuffer(void) :
	GLHandle(0)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCGLFrameBuffer::~VCGLFrameBuffer(void)
{
	
}

void VCGLFrameBuffer::Bind()
{
	if (m_boundFrameBuffer != NULL && m_boundFrameBuffer->GLHandle == GLHandle)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, GLHandle);
	m_boundFrameBuffer = this;

	glErrorCheck();
}

void VCGLFrameBuffer::SetRenderTarget( VCGLTexture* texture )
{
	Bind();
	texture->Bind(-1);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->GLTextID, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		VC_ERROR("Failed to bind texture as Framebuffer render target.");
	}
}

VCGLFrameBuffer* VCGLFrameBuffer::GetDefault()
{
	if (VCGLFrameBuffer::m_defaultFrameBuffer == NULL)
		VCGLFrameBuffer::m_defaultFrameBuffer = new VCGLFrameBuffer();

	return VCGLFrameBuffer::m_defaultFrameBuffer;
}

VCGLFrameBuffer* VCGLFrameBuffer::GetTextureTarget()
{
	if (VCGLFrameBuffer::m_textureTargetFrameBuffer == NULL)
	{
		VCGLFrameBuffer::m_textureTargetFrameBuffer = new VCGLFrameBuffer();

		glGenFramebuffers(1, &VCGLFrameBuffer::m_textureTargetFrameBuffer->GLHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, VCGLFrameBuffer::m_textureTargetFrameBuffer->GLHandle);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			VC_ERROR("Failed to initialize GL FrameBuffer.");
		}
	}

	return VCGLFrameBuffer::m_textureTargetFrameBuffer;
}

int VCInteropVCGLFrameBufferGetDefault()
{
	return VCGLFrameBuffer::GetDefault()->Handle;
}

void VCInteropVCGLFrameBufferBind( int handle )
{
	VCGLFrameBuffer* obj = (VCGLFrameBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->Bind();
}

void VCInteropVCGLFrameBufferSetClearColor( int handle, glm::vec4 color )
{
	VCGLFrameBuffer* obj = (VCGLFrameBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->Bind();
	glClearColor(color.x, color.y, color.z, color.w);
}

void VCInteropVCGLFrameBUfferClear( int handle, bool color, bool depth )
{
	VCGLFrameBuffer* obj = (VCGLFrameBuffer*) VCObjectStore::Instance->GetObject(handle);
	obj->Bind();

	int flags = 0;

	if ( color )
		flags |= GL_COLOR_BUFFER_BIT;

	if ( depth )
		flags |= GL_DEPTH_BUFFER_BIT;
	
	glClear(flags);
}
