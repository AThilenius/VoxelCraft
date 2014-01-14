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
#include "VCShader.h"


VCImageBuilder::VCImageBuilder(void):
	Shader(NULL)
{
}


VCImageBuilder::~VCImageBuilder(void)
{
	// Too lazy to clean up, should be application level anyway.
}

void VCImageBuilder::DrawImage( std::string imagePath, VCRectangle frame, float depthStep )
{
	if (Shader == NULL)
		Shader = VCResourceManager::GetShader("TexturePassThrough");

	auto iter = m_imageInstances.find(imagePath);
	
	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(imagePath);
		// TriLinear Filtering
		newInst->Initialize(Shader, VCTextureParams());
		m_imageInstances.insert(ImageInstMap::value_type(imagePath, newInst));
		newInst->DrawImage(frame, depthStep);
	}

	else
	{
		iter->second->DrawImage(frame, depthStep);
	}
}

void VCImageBuilder::Draw9SliceImage( std::string imagePath, VCRectangle frame, int pizelOffset, float padding, float depthStep )
{
	if (Shader == NULL)
		Shader = VCResourceManager::GetShader("TexturePassThrough");

	auto iter = m_imageInstances.find(imagePath);

	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(imagePath);
		// TriLinear Filtering
		newInst->Initialize(Shader, VCTextureParams());
		m_imageInstances.insert(ImageInstMap::value_type(imagePath, newInst));
		newInst->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}

	else
	{
		iter->second->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}
}
