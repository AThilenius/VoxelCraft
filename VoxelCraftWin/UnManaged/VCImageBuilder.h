//
//  VCImageBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCImageInstance;

class VCImageBuilder
{
public:
	VCImageBuilder(void);
	~VCImageBuilder(void);

	void DrawImage(std::string imagePath, VCRectangle frame, float depthStep);

private:
	typedef std::unordered_map<std::string, VCImageInstance*> ImageInstMap;
	ImageInstMap m_imageInstances;
};