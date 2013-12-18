//
//  VCGLRenderer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCShadowShader;
class VCTexturePassThroughShader;
class VCLexShader;
class VCGuiShader;
class VCColorPassThroughShader;
class VCTerrainConstructionShader;
class VCTerrianFeedbackShader;
class VCVoxelFallbackShader;
class VCRenderStage;

struct _VCRenderStageCompare 
{
	bool operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const;
};

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render(int fromBatch, int toBatch);

	void SetModelMatrix(glm::mat4 matrix);

	void RegisterStage(VCRenderStage* state);
	void UnRegisterStage(VCRenderStage* state);

public:
	// Static
	static VCGLRenderer* Instance;

	// Member
	VCShadowShader* ShadowShader;
	VCTexturePassThroughShader* TexturePassthroughShader;
	VCLexShader* LexShader;
	VCGuiShader* GuiShader;
	VCColorPassThroughShader* ColorPassThroughShader;
	//VCTerrainConstructionShader* TerrainConstructionShader;
	//VCTerrianFeedbackShader* TerrainFeedbackShader;
	VCVoxelFallbackShader* VoxelFallbackShader;
	bool ShadowFallback;

	GLuint DefaultFrameBuffer;
	GLuint DepthFrameBuffer;
	VCTexturePtr DepthTexture;

private:
	void CreateDepthFrameBuffer();

	typedef boost::container::flat_set<VCRenderStage*, _VCRenderStageCompare> RenderSet;
	RenderSet m_renderSet;
};

// Interop
DLL_EXPORT_API void VCInteropRendererRender(int from, int to);