//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCText.h"
#include "VCGeometryBuilder.h"
#include "VCTextBuilder.h"



class VCGui
{
public:
	VCGui(void)
	{
		VCGui::Instance = this;
	}
	~VCGui(void){}

	void Reset()
	{
		Geometry.Reset();
		Text.Reset();
	}

	void Initialize()
	{
		Geometry.Initialize();
		Text.Initialize();
	}

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
void VCInteropGuiDrawRectangle(Rectangle rect, vcint4 color);
void VCInteropGuiDrawText(MonoString* font, MonoString* text, Point point, vcint4 color);

