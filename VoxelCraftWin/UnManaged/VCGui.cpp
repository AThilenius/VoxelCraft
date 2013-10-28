//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGui.h"

#include "VCLexicalEngine.h"

VCGui* VCGui::Instance = NULL;

VCGui::VCGui( void )
{
	VCGui::Instance = this;
}

VCGui::~VCGui( void )
{

}

void VCGui::Reset()
{
	Geometry.Reset();
	Text.Reset();
}

void VCGui::Initialize()
{
	Geometry.Initialize();
	Text.Initialize();
}

void VCGui::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiClear",			(void*)VCInteropGuiClear);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiDrawRectangle",	(void*)VCInteropGuiDrawRectangle);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiDrawEllipse",		(void*)VCInteropGuiDrawEllipse);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiDrawText",		(void*)VCInteropGuiDrawText);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiAddVerticie",		(void*)VCInteropGuiAddVerticie);
	mono_add_internal_call("VCEngine.Gui::VCInteropGuiGetTextMetrics",	(void*)VCInteropGuiGetTextMetrics);
}

void VCInteropGuiClear()
{
	VCGui::Instance->Reset();
}

void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color)
{
	VCGui::Instance->Geometry.DrawRectangle(rect, GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 color)
{
	VCGui::Instance->Geometry.DrawEllipse(centroid, width, height, GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropGuiDrawText(MonoString* font, MonoString* text, VCPoint point, vcint4 color)
{
	char* t = mono_string_to_utf8(text);
	char* f = mono_string_to_utf8(font);

	VCGui::Instance->Text.DrawText(t, point, f, GLubyte4(color.X, color.Y, color.Z, color.W));

	mono_free(t);
	mono_free(f);
}

void VCInteropGuiAddVerticie( GuiRectVerticie vert )
{
	VCGui::Instance->Geometry.AddQuad(vert);
}

void VCInteropGuiGetTextMetrics(MonoString* font, MonoString* text, VCTextMetrics* metrics)
{
	char* t = mono_string_to_utf8(text);
	char* f = mono_string_to_utf8(font);

	*metrics = VCLexicalEngine::Instance->GetMetrics(f, t);

	mono_free(t);
	mono_free(f);
}
