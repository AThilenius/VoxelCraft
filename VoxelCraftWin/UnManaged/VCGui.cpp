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
#include "VCObjectStore.h"
#include "VCRenderStage.h"
#include "VCTextBuilder.h"
#include "VCImageBuilder.h"

VCGui* VCGui::Instance = NULL;
float VCGui::Scale = 1.0f;
float VCGui::InverseScale = 1.0f;

bool _VCRenderStageCompare::operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
{
	return (*lhs) < (*rhs);
}

VCGui::VCGui( void ):
	DepthStep(0)
{
	
}

VCGui::~VCGui( void )
{

}

void VCGui::Initialize()
{
	GuiCamera = new VCCamera();

	Geometry = new VCGeometryBuilder(this);
	Geometry->Initialize();
	Text = new VCTextBuilder(this);
	Text->Initialize();
	ImageBuilder = new VCImageBuilder(this);
}

void VCGui::Render()
{
	static VCRenderStage* lastBoundStage = NULL;
	for ( auto setIter = m_renderSet.begin(); setIter != m_renderSet.end(); setIter++ )
	{
		VCRenderStage* stage = *setIter;

		if (stage->ExectionType == VCRenderStage::ExecutionTypes::Never)
			continue;

		VCRenderStage::TransitionAndExecute(lastBoundStage, stage);
		lastBoundStage = stage;
	}

	DepthStep = 0.0f;
}

void VCGui::AddGUIRenderStage( VCRenderStage* stage )
{
	stage->BuildKey();

#ifdef DEBUG
	if (m_renderSet.find(stage) != m_renderSet.end())
		VCLog::Error("Cannot add duplicate render stage!", "Rendering");
#endif

	m_renderSet.insert(stage);
}

void VCGui::RemoveGUIRenderStage( VCRenderStage* stage )
{
	auto iter = m_renderSet.find(stage);

	if (iter == m_renderSet.end())
		VCLog::Error("Cannot remove RenderState because it is not registered.", "Rendering");

	m_renderSet.erase(iter);
}

void VCInteropGuiSetScale( float scale )
{
	VCGui::Scale = scale;
	VCGui::InverseScale = 1.0f / scale;
}

void VCInteropGuiRender()
{
	VCGui::Instance->Render();
}

void VCInteropGuiDrawRectangle(VCRectangle rect, vcint4 color)
{
	VCGui::Instance->Geometry->DrawRectangle(rect, GLubyte4(color.X, color.Y, color.Z, color.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiDrawEllipse(VCPoint centroid, int width, int height, vcint4 top, vcint4 bottom)
{
	VCGui::Instance->Geometry->DrawEllipse(centroid, width, height, GLubyte4(top.X, top.Y, top.Z, top.W), GLubyte4(bottom.X, bottom.Y, bottom.Z, bottom.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiAddVerticie( GuiRectVerticie vert )
{
	VCGui::Instance->Geometry->AddQuad(vert, VCGui::Instance->DepthStep++);
}

void VCInteropGuiDrawText(int font,char* text, VCPoint point, vcint4 color)
{
	VCGui::Instance->Text->DrawText(font, text, point, GLubyte4(color.X, color.Y, color.Z, color.W), VCGui::Instance->DepthStep++);
}

void VCInteropGuiGetTextMetrics(int font, char* text, VCTextMetrics* metrics)
{
	*metrics = VCLexicalEngine::Instance->GetMetrics(font, text);
}

void VCInteropGuiDrawImage( int texHandle, VCRectangle frame )
{
	VCGLTexture* obj = (VCGLTexture*) VCObjectStore::Instance->GetObject(texHandle);
	VCGui::Instance->ImageBuilder->DrawImage(obj, frame, VCGui::Instance->DepthStep++);
}

void VCInteropGuiDraw9SliceImage( int texHandle, VCRectangle frame, int pizelOffset, float padding )
{
	VCGLTexture* obj = (VCGLTexture*) VCObjectStore::Instance->GetObject(texHandle);
	VCGui::Instance->ImageBuilder->Draw9SliceImage(obj, frame, pizelOffset, padding, VCGui::Instance->DepthStep++);
}