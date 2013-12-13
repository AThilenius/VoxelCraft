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
#include "VCMonoString.h"
#include "VCCamera.h"

VCGui* VCGui::Instance = NULL;
float VCGui::Scale = 1.0f;
float VCGui::InverseScale = 1.0f;

VCGui::VCGui( void ):
	DepthStep(2)
{
	VCGui::Instance = this;
}

VCGui::~VCGui( void )
{

}

void VCGui::Initialize()
{
	GuiCamera = new VCCamera();
	Geometry.Initialize();
	Text.Initialize();
}

void VCGui::RegisterMonoHandlers()
{
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiSetScale",			(void*)VCInteropGuiSetScale);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiResetDepth",			(void*)VCInteropGuiResetDepth);

	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawRectangle",		(void*)VCInteropGuiDrawRectangle);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawEllipse",		(void*)VCInteropGuiDrawEllipse);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiAddVerticie",		(void*)VCInteropGuiAddVerticie);
	VCMonoRuntime::SetMethod("Gui::VCInteropGuiDrawImage",			(void*)VCInteropGuiDrawImage);

	VCMonoRuntime::SetMethod("Font::VCInteropGuiDrawText",			(void*)VCInteropGuiDrawText);
	VCMonoRuntime::SetMethod("Font::VCInteropGuiGetTextMetrics",	(void*)VCInteropGuiGetTextMetrics);
}

void VCInteropGuiSetScale( float scale )
{
	VCGui::Scale = scale;
	VCGui::InverseScale = 1.0f / scale;
}

void VCInteropGuiResetDepth()
{
	VCGui::Instance->DepthStep = 2;
}

void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color)
{
	VCGui::Instance->Geometry.DrawRectangle(rect, GLubyte4(color.X, color.Y, color.Z, color.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 top, vcint4 bottom)
{
	VCGui::Instance->Geometry.DrawEllipse(centroid, width, height, GLubyte4(top.X, top.Y, top.Z, top.W), GLubyte4(bottom.X, bottom.Y, bottom.Z, bottom.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiAddVerticie( GuiRectVerticie vert )
{
	VCGui::Instance->Geometry.AddQuad(vert, VCGui::Instance->DepthStep++);
}

void VCInteropGuiDrawText(int font,VCMonoStringPtr text, VCPoint point, vcint4 color)
{
	VCGui::Instance->Text.DrawText(font, VCMonoString(text), point, GLubyte4(color.X, color.Y, color.Z, color.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiGetTextMetrics(int font, VCMonoStringPtr text, VCTextMetrics* metrics)
{
	*metrics = VCLexicalEngine::Instance->GetMetrics(font, VCMonoString(text));
}

void VCInteropGuiDrawImage( VCMonoStringPtr path, VCRectangle frame )
{
	VCGui::Instance->ImageBuilder.DrawImage(VCMonoString(path), frame, VCGui::Instance->DepthStep++);
}
