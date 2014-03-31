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

bool _VCRenderStageCompare::operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
{
	return (*lhs) < (*rhs);
}

VCGui::VCGui( void ):
	DepthStep(0),
	Scale(1.0f),
	InverseScale(1.0f)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
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

int VCInteropGuiCreate()
{
	VCGui* gui = new VCGui();
	gui->Initialize();
	return gui->Handle;
}

void VCInteropGuiRelease( int handle )
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropGuiSetScale(int handle, float scale)
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->Scale = scale;
	obj->InverseScale = 1.0f / scale;
}

void VCInteropGuiRender(int handle)
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->Render();
}

void VCInteropGuiDrawRectangle(int handle, VCRectangle rect, vcint4 color)
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->Geometry->DrawRectangle(rect, GLubyte4(color.X, color.Y, color.Z, color.W), obj->DepthStep++);
}

void VCInteropGuiDrawEllipse(int handle, VCPoint centroid, int width, int height, vcint4 top, vcint4 bottom)
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->Geometry->DrawEllipse(centroid, width, height, GLubyte4(top.X, top.Y, top.Z, top.W), GLubyte4(bottom.X, bottom.Y, bottom.Z, bottom.W), obj->DepthStep++);
}

void VCInteropGuiAddVerticie(int handle, GuiRectVerticie vert )
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->Geometry->AddQuad(vert, obj->DepthStep++);
}

void VCInteropGuiDrawText(int handle, int font, char* text, VCPoint point, vcint4 color)
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	obj->DepthStep++;
	obj->Text->DrawText(font, text, point, GLubyte4(color.X, color.Y, color.Z, color.W), &obj->DepthStep);
}

void VCInteropGuiGetTextMetrics(int handle, int font, char* text, VCTextMetrics* metrics)
{
	*metrics = VCLexicalEngine::Instance->GetMetrics(font, text);
}

void VCInteropGuiDrawImage(int handle, int texHandle, VCRectangle frame )
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	VCGLTexture* tex = (VCGLTexture*) VCObjectStore::Instance->GetObject(texHandle);
	obj->ImageBuilder->DrawImage(tex, frame, obj->DepthStep++);
}

void VCInteropGuiDraw9SliceImage(int handle, int texHandle, VCRectangle frame, int pizelOffset, float padding )
{
	VCGui* obj = (VCGui*) VCObjectStore::Instance->GetObject(handle);
	VCGLTexture* tex = (VCGLTexture*) VCObjectStore::Instance->GetObject(texHandle);
	obj->ImageBuilder->Draw9SliceImage(tex, frame, pizelOffset, padding, obj->DepthStep++);
}
