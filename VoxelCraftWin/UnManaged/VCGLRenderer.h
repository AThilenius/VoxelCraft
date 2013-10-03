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
#include "VCIRenderable.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render();

	void SetModelMatrix(mat4 matrix);

	void RegisterState(VCRenderState* state);

	void RegisterIRenderable(VCIRenderable* renderable);
	void UnRegisterIRenderable(VCIRenderable* renderable);

public:
	void CreateDepthFrameBuffer();

	static VCGLRenderer* Instance;

	VCVoxelShader* VoxelShader;
	VCShadowShader* ShadowShader;
	VCTextureShader* TextureShader;
	VCLexShader* LexShader;

	GLuint DefaultFrameBuffer;
	GLuint DepthFrameBuffer;
	GLuint DepthTexture;

private:
	typedef std::set<VCIRenderable*> RenderSet;
	typedef std::map<VCRenderState*, RenderSet, _VCRenderStateCompare> RenderMap;

	RenderMap m_renderMap;


	// Debug
	GLuint m_quad_VertexArrayID;

};

