//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCRenderStage.h"
#include "VCGLTexture.h"
#include "VCGLWindow.h"
#include "VCRenderStage.h"
#include "VCCamera.h"

VCRenderStage::VCRenderStage(VCVoidDelegate function):
	Key(0),
	BatchOrder(VC_BATH_DEFAULT),
	StageOrder(0),
	FrameBuffer(0),
	Shader(NULL),
	Texture(NULL),
	Blend(true),
	DepthTest(true),
	ExecutionFunction(function),
	ExectionType(VCRenderStage::Always),
	Camera(NULL)
{
}

VCRenderStage::~VCRenderStage(void)
{
}

void VCRenderStage::BuildKey()
{
	// =====   Safety Checks   ======================================================
	if (
		BatchOrder > ( 1 << 3 ) ||
		StageOrder > ( 1 << 3 ) ||
		FrameBuffer > ( 1 << 3 ) ||
		Shader->m_programId > ( 1 << 7 ) ||
		(Texture != NULL && Texture->GLTextID > ( 1 << 15 )) )
	{
		VC_ERROR("Max value exceeded. Can not bit pack field.");
	}

	// =====   Packing   ======================================================
	Key = 0;

	Key |= ( (UInt64)BatchOrder				<< (64 - 4) );
	Key |= ( (UInt64)StageOrder				<< (64 - 8) );
	Key |= ( (UInt64)FrameBuffer			<< (64 - 12) );
	Key |= ( (UInt64)Shader->m_programId	<< (64 - 20) );
	if (Texture != NULL)
		Key |= ( (UInt64)Texture->GLTextID	<< (64 - 36) );
	Key |= ( (UInt64)DepthTest				<< (64 - 37) );
	Key |= ( (UInt64)Blend					<< (64 - 38) );
}

void VCRenderStage::TransitionAndExecute( VCRenderStage* fromState, VCRenderStage* toState )
{
	if (toState->ExectionType == VCRenderStage::Once)
		toState->ExectionType = VCRenderStage::Never;

	// Blindly set the toState
	if (fromState == NULL)
	{
		// Viewport
		if (toState->Camera == NULL)
			glViewport(VCGLWindow::ActiveWindow->FullViewport.X, VCGLWindow::ActiveWindow->FullViewport.Y, VCGLWindow::ActiveWindow->FullViewport.Width, VCGLWindow::ActiveWindow->FullViewport.Height);

		else
		{
#ifdef DEBUG
			if( toState->Camera->Viewport.Width < 1 || toState->Camera->Viewport.Height < 1 )
				VCLog::Error("Invalid Viewport!", "Rendering");
#endif
			glViewport(toState->Camera->Viewport.X, toState->Camera->Viewport.Y, toState->Camera->Viewport.Width, toState->Camera->Viewport.Height);
		}

		// Camera
		VCCamera::BoundCamera = toState->Camera;

		// Shader
		toState->Shader->Bind();
		//if (toState->Camera != NULL)
		//	toState->Shader->SetCamera(toState->Camera);

		// Texture
		if (toState->Texture != NULL)
			toState->Texture->Bind(0);

		// DepthTest
		//if (toState->DepthTest)
		//	glEnable(GL_DEPTH_TEST);
		//else
		//	glDisable(GL_DEPTH_TEST);

		// Blend
		//if (toState->Blend)
		//	glEnable(GL_BLEND);
		//else
		//	glDisable(GL_BLEND);

	}

	// Transition fromState -> toState
	else
	{
		// Viewport
		static VCRectangle lastViewport;
		if (toState->Camera == NULL)
			glViewport(VCGLWindow::ActiveWindow->FullViewport.X, VCGLWindow::ActiveWindow->FullViewport.Y, VCGLWindow::ActiveWindow->FullViewport.Width, VCGLWindow::ActiveWindow->FullViewport.Height);

		else if (toState->Camera != NULL)
			glViewport(toState->Camera->Viewport.X, toState->Camera->Viewport.Y, toState->Camera->Viewport.Width, toState->Camera->Viewport.Height);

		// Camera
		VCCamera::BoundCamera = toState->Camera;

		// Shader
		toState->Shader->Bind();
		//if (toState->Camera != NULL)
		//	toState->Shader->SetCamera(toState->Camera);

		// Texture
		if (toState->Texture != NULL)
			toState->Texture->Bind(0);

		// DepthTest
		//if (fromState->DepthTest != toState->DepthTest)
		//{
		//	if(toState->DepthTest)	glEnable(GL_DEPTH_TEST);
		//	else					glDisable(GL_DEPTH_TEST);
		//}

		//// Blend
		//if (fromState->Blend != toState->Blend)
		//{
		//	if (toState->Blend)	glEnable(GL_BLEND);
		//	else				glDisable(GL_BLEND);
		//}
	}

	// Execute
	toState->ExecutionFunction();
}

bool operator==(const VCRenderStage& lhs, const VCRenderStage& rhs)
{
	if (lhs.Key == 0 || rhs.Key == 0)
	{
		VC_ERROR("Cannot compare unbuilt VCRenderStages.");
	}

	if (lhs.Key != rhs.Key)
		return false;

	// TODO: Undefined behavior, add overloads to delegate template
	return lhs.ExecutionFunction == rhs.ExecutionFunction;
}

bool operator< (const VCRenderStage& lhs, const VCRenderStage& rhs)
{
	if (lhs.Key == 0 || rhs.Key == 0)
	{
		VC_ERROR("Cannot compare unbuilt VCRenderStages.");
	}

	if (lhs.Key < rhs.Key) return true;
	if (lhs.Key > rhs.Key) return false;

	// TODO: Undefined behavior, add overloads to delegate template
	return lhs.ExecutionFunction < rhs.ExecutionFunction;
}

bool operator!=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator==(lhs,rhs);}
bool operator> (const VCRenderStage& lhs, const VCRenderStage& rhs){return  operator< (rhs,lhs);}
bool operator<=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator> (lhs,rhs);}
bool operator>=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator< (lhs,rhs);}