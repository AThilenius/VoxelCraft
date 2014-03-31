//
//  VCImageBuilder.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCImageBuilder.h"

#include "VCImageInstance.h"
#include "VCResourceManager.h"
#include "VCGLShader.h"


VCImageBuilder::VCImageBuilder(VCGui* gui):
	Shader(NULL),
	m_parentGui(gui)
{
}


VCImageBuilder::~VCImageBuilder(void)
{
	// Too lazy to clean up, should be application level anyway.
}

void VCImageBuilder::DrawImage( VCGLTexture* tex, VCRectangle frame, float depthStep )
{
	if (Shader == NULL)
		Shader = VCResourceManager::GetShader("TexturePassThrough");

	auto iter = m_imageInstances.find(tex);
	
	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(m_parentGui, tex);
		// TriLinear Filtering
		newInst->Initialize(Shader, VCTextureParams());
		m_imageInstances.insert(ImageInstMap::value_type(tex, newInst));
		newInst->DrawImage(frame, depthStep);
	}

	else
	{
		iter->second->DrawImage(frame, depthStep);
	}
}

void VCImageBuilder::Draw9SliceImage( VCGLTexture* tex, VCRectangle frame, int pizelOffset, float padding, float depthStep )
{
	if (Shader == NULL)
		Shader = VCResourceManager::GetShader("TexturePassThrough");

	auto iter = m_imageInstances.find(tex);

	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(m_parentGui, tex);
		// TriLinear Filtering
		newInst->Initialize(Shader, VCTextureParams());
		m_imageInstances.insert(ImageInstMap::value_type(tex, newInst));
		newInst->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}

	else
	{
		iter->second->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}
}
