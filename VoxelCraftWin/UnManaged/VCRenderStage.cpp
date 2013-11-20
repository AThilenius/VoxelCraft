//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCRenderStage.h"
#include "VCTexture.h"
#include "VCWindow.h"
#include "VCRenderStage.h"
#include "VCCamera.h"

VCRenderStage::VCRenderStage(VCVoidDelegate function):
	Key(0),
	BatchOrder(VC_BATH_DEFAULT),
	StageOrder(0),
	FrameBuffer(0),
	Shader(NULL),
	Texture(VCTexturePtr(NULL)),
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
		(Texture != VCTexturePtr(NULL) && Texture->m_glTextID > ( 1 << 15 )) )
	{
		VC_ERROR("Max value exceeded. Can not bit pack field.");
	}

	// =====   Packing   ======================================================
	Key = 0;

	Key |= ( (UInt64)BatchOrder				<< (64 - 4) );
	Key |= ( (UInt64)StageOrder				<< (64 - 8) );
	Key |= ( (UInt64)FrameBuffer			<< (64 - 12) );
	Key |= ( (UInt64)Shader->m_programId	<< (64 - 20) );
	if (Texture != VCTexturePtr(NULL))
		Key |= ( (UInt64)Texture->m_glTextID	<< (64 - 36) );
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
		// Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, toState->FrameBuffer);

		// Viewport
		if (toState->Camera == NULL)
			glViewport(VCWindow::Instance->FullViewport.X, VCWindow::Instance->FullViewport.Y, VCWindow::Instance->FullViewport.Width, VCWindow::Instance->FullViewport.Height);

		else
			glViewport(toState->Camera->Viewport.X, toState->Camera->Viewport.Y, toState->Camera->Viewport.Width, toState->Camera->Viewport.Height);

		// Shader
		toState->Shader->Bind(toState->Camera);

		// Texture
		if (toState->Texture != VCTexturePtr(NULL))
			toState->Texture->Bind(0);

		// DepthTest
		if (toState->DepthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		// Blend
		if (toState->Blend)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	// Transition fromState -> toState
	else
	{
		// Framebuffer
		if (fromState->FrameBuffer != toState->FrameBuffer)
			glBindFramebuffer(GL_FRAMEBUFFER, toState->FrameBuffer);

		// Viewport
		static VCRectangle lastViewport;
		if (toState->Camera == NULL && lastViewport != VCWindow::Instance->FullViewport)
		{
			lastViewport = VCWindow::Instance->FullViewport;
			glViewport(VCWindow::Instance->FullViewport.X, VCWindow::Instance->FullViewport.Y, VCWindow::Instance->FullViewport.Width, VCWindow::Instance->FullViewport.Height);
		}

		else if (toState->Camera->Viewport != lastViewport)
		{
			lastViewport = toState->Camera->Viewport;
			glViewport(toState->Camera->Viewport.X, toState->Camera->Viewport.Y, toState->Camera->Viewport.Width, toState->Camera->Viewport.Height);
		}

		// Shader
		toState->Shader->Bind(toState->Camera);

		// Texture
		if (toState->Texture != VCTexturePtr(NULL))
			toState->Texture->Bind(0);

		// DepthTest
		if (fromState->DepthTest != toState->DepthTest)
		{
			if(toState->DepthTest)	glEnable(GL_DEPTH_TEST);
			else					glDisable(GL_DEPTH_TEST);
		}

		// Blend
		if (fromState->Blend != toState->Blend)
		{
			if (toState->Blend)	glEnable(GL_BLEND);
			else				glDisable(GL_BLEND);
		}
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