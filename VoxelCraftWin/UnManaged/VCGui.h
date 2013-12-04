//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

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
	static VCGui* Instance;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop

// Geometry
void VCInteropGuiAddVerticie(GuiRectVerticie vert);
void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color);
void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 color);

// Text
void VCInteropGuiDrawText(int font, VCMonoStringPtr text, VCPoint point, vcint4 color);
void VCInteropGuiGetTextMetrics(int font, VCMonoStringPtr text, VCTextMetrics* metrics);

// Images
void VCInteropGuiDrawImage(VCMonoStringPtr path, VCRectangle frame);