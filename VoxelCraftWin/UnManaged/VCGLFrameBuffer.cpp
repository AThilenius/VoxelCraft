//
//  VCGLFrameBuffer.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/26/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLFrameBuffer.h"
#include "VCTexture.h"

VCGLFrameBuffer* VCGLFrameBuffer::m_boundFrameBuffer = NULL;
VCGLFrameBuffer* VCGLFrameBuffer::m_defaultFrameBuffer = NULL;
VCGLFrameBuffer* VCGLFrameBuffer::m_textureTargetFrameBuffer = NULL;

VCGLFrameBuffer::VCGLFrameBuffer(void) :
	GLHandle(0)
{
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

void VCGLFrameBuffer::SetRenderTarget( VCTexture* texture )
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