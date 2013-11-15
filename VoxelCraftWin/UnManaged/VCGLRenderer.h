//
//  VCGLRenderer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCVoxelShader;
class VCShadowShader;
class VCTextureShader;
class VCLexShader;
class VCGuiShader;
class VCColorPassThroughShader;
class VCTerrianShader;
class VCRenderState;
class VCIRenderable;

#include <map>
#include <set>
#include "VCRenderState.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render(int fromBatch, int toBatch);

	void SetModelMatrix(glm::mat4 matrix);

	void RegisterState(VCRenderState* state);
	void UnRegisterState(VCRenderState* state);

	void RegisterIRenderable(VCIRenderable* renderable);
	void UnRegisterIRenderable(VCIRenderable* renderable);

public:
	// Static
	static VCGLRenderer* Instance;
	static VCRenderState* PassThroughState;

	// Member
	VCVoxelShader* VoxelShader;
	VCShadowShader* ShadowShader;
	VCTextureShader* TextureShader;
	VCLexShader* LexShader;
	VCGuiShader* GuiShader;
	VCColorPassThroughShader* ColorPassThroughShader;
	VCTerrianShader* TerrainShader;
	bool ShadowFallback;

	GLuint DefaultFrameBuffer;
	GLuint DepthFrameBuffer;
	VCTexturePtr DepthTexture;

private:
	void CreateDepthFrameBuffer();

	typedef std::set<VCIRenderable*> RenderSet;
	typedef std::map<VCRenderState*, RenderSet, _VCRenderStateCompare> RenderMap;

	RenderMap m_renderMap;


	// Debug
	GLuint m_quad_VertexArrayID;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
void VCInteropRendererRender(int from, int to);