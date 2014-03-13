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
#include "VCCamera.h"
#include "VCGLShader.h"
#include "VCResourceManager.h"

VCGui* VCGui::Instance = NULL;
float VCGui::Scale = 1.0f;
float VCGui::InverseScale = 1.0f;

VCGui::VCGui( void ):
	DepthStep(2),
	GuiColorUniformIndex(-1)
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
	GuiImages.Shader = VCResourceManager::GetShader("GuiPackedChannels");
	GuiColorUniformIndex = GuiImages.Shader->GetUniformIndex("Color");
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

void VCInteropGuiDrawText(int font,char* text, VCPoint point, vcint4 color)
{
	VCGui::Instance->Text.DrawText(font, text, point, GLubyte4(color.X, color.Y, color.Z, color.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiGetTextMetrics(int font, char* text, VCTextMetrics* metrics)
{
	*metrics = VCLexicalEngine::Instance->GetMetrics(font, text);
}

void VCInteropGuiDrawImage( char* path, VCRectangle frame )
{
	VCGui::Instance->ImageBuilder.DrawImage(path, frame, VCGui::Instance->DepthStep++);
}

void VCInteropGuiDraw9SliceImage( char* path, VCRectangle frame, int pizelOffset, float padding )
{
	VCGui::Instance->ImageBuilder.Draw9SliceImage(path, frame, pizelOffset, padding, VCGui::Instance->DepthStep++);
}

void VCInteropGuiDraw9SliceGui( char* path, vcint4 color, VCRectangle frame, int pizelOffset, float padding )
{
	VCGui::Instance->GuiImages.Shader->Bind();
	VCGui::Instance->GuiImages.Shader->SetUniform(VCGui::Instance->GuiColorUniformIndex, glm::vec4(color.X / 255.0f, color.Y / 255.0f, color.Z / 255.0f, color.W / 255.0f));

	VCGui::Instance->GuiImages.Draw9SliceImage(path, frame, pizelOffset, padding, VCGui::Instance->DepthStep++);
}
