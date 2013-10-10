//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGui.h"

VCGui* VCGui::Instance = NULL;

void VCGui::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiClear",			(void*)VCInteropGuiClear);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiDrawRectangle",	(void*)VCInteropGuiDrawRectangle);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiDrawText",		(void*)VCInteropGuiDrawText);
}

void VCInteropGuiClear()
{
	VCGui::Instance->Reset();
}

void VCInteropGuiDrawRectangle(Rectangle rect, vcint4 color)
{
	VCGui::Instance->Geometry.DrawRectangle(rect, GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropGuiDrawText(MonoString* font, MonoString* text, Point point, vcint4 color)
{
	VCGui::Instance->Text.DrawText(mono_string_to_utf8(text), point, mono_string_to_utf8(font), GLubyte4(color.X, color.Y, color.Z, color.W));
}

