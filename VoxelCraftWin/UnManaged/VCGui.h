//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define VC_GUI_DEPTH_STEP_SIZE 1.0f

class VCCamera;
class VCRenderStage;
class VCTextBuilder;
class VCImageBuilder;
struct VCTextMetrics;

#include "VCGeometryBuilder.h"

struct _VCRenderStageCompare 
{
	bool operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const;
};

class VCGui
{
public:
	VCGui(void);
	~VCGui(void);

	void Initialize();
	void Render();
	void AddGUIRenderStage(VCRenderStage* stage);
	void RemoveGUIRenderStage(VCRenderStage* stage);

public:
	VCGeometryBuilder* Geometry;
	VCTextBuilder* Text;
	VCImageBuilder* ImageBuilder;
	VCCamera* GuiCamera;

public:
	float DepthStep;

	static VCGui* Instance;
	static float Scale;
	static float InverseScale;

private:
	typedef boost::container::flat_set<VCRenderStage*, _VCRenderStageCompare> RenderSet;
	RenderSet m_renderSet;
};

// Interop
DLL_EXPORT_API void VCInteropGuiSetScale(float scale);
DLL_EXPORT_API void VCInteropGuiRender();

// Geometry
DLL_EXPORT_API void VCInteropGuiAddVerticie(GuiRectVerticie vert);
DLL_EXPORT_API void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color);
DLL_EXPORT_API void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 top, vcint4 bottom);

// Text
DLL_EXPORT_API void VCInteropGuiDrawText(int font, char* text, VCPoint point, vcint4 color);
DLL_EXPORT_API void VCInteropGuiGetTextMetrics(int font, char* text, VCTextMetrics* metrics);

// Images
DLL_EXPORT_API void VCInteropGuiDrawImage(int texHandle, VCRectangle frame);
DLL_EXPORT_API void VCInteropGuiDraw9SliceImage(int texHandle, VCRectangle frame, int pizelOffset, float padding);