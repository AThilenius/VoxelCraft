//
//  VCGLFrameBuffer.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/26/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLTexture;

#include "VCMarshalableObject.h"

class VCGLFrameBuffer : public VCMarshalableObject
{
public:
	~VCGLFrameBuffer();

	void Bind();
	void SetRenderTarget(VCGLTexture* texture);

	static VCGLFrameBuffer* GetDefault();
	static VCGLFrameBuffer* GetTextureTarget();

public:
	GLuint GLHandle;

private:
	VCGLFrameBuffer();

private:
	static VCGLFrameBuffer* m_boundFrameBuffer;
	static VCGLFrameBuffer* m_defaultFrameBuffer;
	static VCGLFrameBuffer* m_textureTargetFrameBuffer;
};

DLL_EXPORT_API int VCInteropVCGLFrameBufferGetDefault();

DLL_EXPORT_API void VCInteropVCGLFrameBufferBind(int handle);
DLL_EXPORT_API void VCInteropVCGLFrameBufferSetClearColor(int handle, glm::vec4 color);
DLL_EXPORT_API void VCInteropVCGLFrameBUfferClear(int handle, bool color, bool depth);