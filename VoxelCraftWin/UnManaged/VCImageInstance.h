//
//  VCImageInstance.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define VC_TEXTURE_BUILDER_START_VERT_SIZE 60

class VCRenderStage;
class VCGLShader;
class VCGLBuffer;

#include "VCGLTexture.h"

struct VCTextureVerticie
{
	VCTextureVerticie();
	VCTextureVerticie(GLfloat3 position, GLfloat2 uv );

	GLfloat3 Position;
	GLfloat2 UV;
};

class VCImageInstance
{
public:
	VCImageInstance(VCGLTexture* tex);
	~VCImageInstance(void);

	void Initialize(VCGLShader* shader, VCTextureParams params);
	void DrawImage (VCRectangle frame, float depthStep);
	void Draw9Slice(VCRectangle frame, int pizelOffset, float padding, float depthStep);

private:
	void Render();

private:
	VCRenderStage* m_rStage;
	VCGLTexture* m_texturePtr;
	
	VCTextureVerticie* m_vertBuffer;
	int m_vertBufferSize;
	GLint m_vertexCount;
	VCGLBuffer* m_gpuBuffer;
};

