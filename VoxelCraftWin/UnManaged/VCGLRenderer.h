//
//  VCGLRenderer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define SHOW_GL_WARNINGS

class VCRenderStage;
class VCIRenderable;

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

	void RegisterStage(VCRenderStage* state);
	void UnRegisterStage(VCRenderStage* state);

	void AddRenderable (VCIRenderable* renderable);

public:
	// Static
	static VCGLRenderer* Instance;

	// Member
	bool ShadowFallback;

	GLuint DefaultFrameBuffer;
	GLuint DepthFrameBuffer;
	VCGLTexture* DepthTexture;

private:
	void CreateDepthFrameBuffer();

	typedef boost::container::flat_set<VCRenderStage*, _VCRenderStageCompare> RenderSet;
	typedef boost::container::flat_set<VCIRenderable*> RenderableSet;
	RenderSet m_renderSet;
	RenderableSet m_renderables;
};

// Interop
DLL_EXPORT_API void VCInteropRendererRender(int from, int to);