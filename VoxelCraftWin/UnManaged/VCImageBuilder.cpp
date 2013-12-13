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


VCImageBuilder::VCImageBuilder(void)
{
}


VCImageBuilder::~VCImageBuilder(void)
{
	// Too lazy to clean up, should be application level anyway.
}

void VCImageBuilder::DrawImage( std::string imagePath, VCRectangle frame, float depthStep )
{
	auto iter = m_imageInstances.find(imagePath);
	
	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(imagePath);
		newInst->Initialize();
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
	auto iter = m_imageInstances.find(imagePath);

	if(iter == m_imageInstances.end())
	{
		VCImageInstance* newInst = new VCImageInstance(imagePath);
		newInst->Initialize();
		m_imageInstances.insert(ImageInstMap::value_type(imagePath, newInst));
		newInst->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}

	else
	{
		iter->second->Draw9Slice(frame, pizelOffset, padding, depthStep);
	}
}
