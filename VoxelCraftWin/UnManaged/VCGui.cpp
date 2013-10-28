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
#include "VCMonoRuntime.h"

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
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiClear",				(void*)VCInteropGuiClear);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawRectangle",		(void*)VCInteropGuiDrawRectangle);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawEllipse",		(void*)VCInteropGuiDrawEllipse);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawText",			(void*)VCInteropGuiDrawText);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiAddVerticie",		(void*)VCInteropGuiAddVerticie);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiGetTextMetrics",		(void*)VCInteropGuiGetTextMetrics);
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

void VCInteropGuiDrawText(VCMonoStringPtr font,VCMonoStringPtr text, VCPoint point, vcint4 color)
{
	VCGui::Instance->Text.DrawText(VCMonoString(text), point, VCMonoString(font), GLubyte4(color.X, color.Y, color.Z, color.W));
}

void VCInteropGuiAddVerticie( GuiRectVerticie vert )
{
	VCGui::Instance->Geometry.AddQuad(vert);
}

void VCInteropGuiGetTextMetrics(VCMonoStringPtr font, VCMonoStringPtr text, VCTextMetrics* metrics)
{
	*metrics = VCLexicalEngine::Instance->GetMetrics(VCMonoString(font), VCMonoString(text));
}
