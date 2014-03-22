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
struct VCTextMetrics;

#include "VCGeometryBuilder.h"
#include "VCTextBuilder.h"
#include "VCImageBuilder.h"

class VCGui
{
public:
	VCGui(void);
	~VCGui(void);

	void Initialize();

	VCGeometryBuilder Geometry;
	VCTextBuilder Text;
	VCImageBuilder ImageBuilder;
	VCImageBuilder GuiImages;
	VCCamera* GuiCamera;
	int GuiColorUniformIndex;

public:
	float DepthStep;

	static VCGui* Instance;
	static float Scale;
	static float InverseScale;
};

// Interop
DLL_EXPORT_API void VCInteropGuiSetScale(float scale);
DLL_EXPORT_API void VCInteropGuiResetDepth();

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

// GUI Images
DLL_EXPORT_API void VCInteropGuiDraw9SliceGui(int texHandle, vcint4 color, VCRectangle frame, int pizelOffset, float padding);