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
class VCShader;

#include "VCTexture.h"

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
	VCImageInstance(std::string path);
	~VCImageInstance(void);

	void Initialize(VCShader* shader, VCTextureParams params);
	void DrawImage (VCRectangle frame, float depthStep);
	void Draw9Slice(VCRectangle frame, int pizelOffset, float padding, float depthStep);

private:
	void Render();

private:
	std::string m_path;
	VCRenderStage* m_rStage;
	VCTexture* m_texturePtr;
	
	GLuint m_VAO;
	GLuint m_VBO;
	VCTextureVerticie* m_vertBuffer;
	int m_vertBufferSize;
	GLint m_vertexCount;
};

