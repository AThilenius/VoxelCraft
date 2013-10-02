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
#include "VCLexShader.h"
#include "VCRenderable.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render();

	void SetModelMatrix(mat4 matrix);

	void RegisterState(VCRenderState* state);

	void RegisterRenderable(VCRenderable* renderable);
	void UnRegisterRenderable(VCRenderable* renderable);

public:
	static VCGLRenderer* Instance;

	VCVoxelShader* VoxelShader;
	VCShadowShader* ShadowShader;
	VCTextureShader* TextureShader;
	VCLexShader* LexShader;

	GLuint DefaultFrameBuffer;
	GLuint DepthFrameBuffer;
	GLuint DepthTexture;

private:
	typedef std::set<VCRenderable*, _VCRenderableCompare> RenderSet;
	typedef std::map<VCRenderState*, RenderSet, _VCRenderStateCompare> RenderMap;

	RenderMap m_renderMap;


	// Debug
	GLuint m_textVAO;
	GLuint m_quad_VertexArrayID;
	GLuint m_textTexture;

};

