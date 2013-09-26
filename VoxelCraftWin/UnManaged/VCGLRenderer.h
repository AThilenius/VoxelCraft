//
//  VCGLRenderer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCVoxelShader.h"
#include "VCShadowShader.h"
#include "VCTextureShader.h"
#include "VCCamera.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render();

	void SetModelMatrix(mat4 matrix);

public:
	static VCGLRenderer* Instance;

	VCVoxelShader* VoxelShader;
	VCShadowShader* ShadowShader;
	VCTextureShader* TextureShader;

private:
	GLuint m_frameBufferId;
	GLuint m_depthTexture;

	// Debug
	GLuint m_quad_VertexArrayID;

};

