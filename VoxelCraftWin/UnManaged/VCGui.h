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
#include "VCMonoString.h"

class VCGui
{
public:
	VCGui(void);
	~VCGui(void);

	void Initialize();

	VCGeometryBuilder Geometry;
	VCTextBuilder Text;
	VCImageBuilder ImageBuilder;
	VCCamera* GuiCamera;

public:
	float DepthStep;

	static VCGui* Instance;
	static float Scale;
	static float InverseScale;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
void VCInteropGuiSetScale(float scale);
void VCInteropGuiResetDepth();

// Geometry
void VCInteropGuiAddVerticie(GuiRectVerticie vert);
void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color);
void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 top, vcint4 bottom);

// Text
void VCInteropGuiDrawText(int font, VCMonoStringPtr text, VCPoint point, vcint4 color);
void VCInteropGuiGetTextMetrics(int font, VCMonoStringPtr text, VCTextMetrics* metrics);

// Images
void VCInteropGuiDrawImage(VCMonoStringPtr path, VCRectangle frame);
void VCInteropGuiDraw9SliceImage(VCMonoStringPtr path, VCRectangle frame, int pizelOffset, float padding);