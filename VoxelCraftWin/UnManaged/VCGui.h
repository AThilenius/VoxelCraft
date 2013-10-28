//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct VCTextMetrics;

#include "VCGeometryBuilder.h"
#include "VCTextBuilder.h"

class VCGui
{
public:
	VCGui(void);
	~VCGui(void);

	void Reset();
	void Initialize();

	VCGeometryBuilder Geometry;
	VCTextBuilder Text;

public:
	static VCGui* Instance;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
void VCInteropGuiClear();
void VCInteropGuiAddVerticie(GuiRectVerticie vert);
void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color);
void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 color);
void VCInteropGuiDrawText(MonoString* font, MonoString* text, VCPoint point, vcint4 color);
void VCInteropGuiGetTextMetrics(MonoString* font, MonoString* text, VCTextMetrics* metrics);