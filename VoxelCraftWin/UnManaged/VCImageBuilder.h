//
//  VCImageBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCImageInstance;
class VCShader;

class VCImageBuilder
{
public:
	VCImageBuilder(void);
	~VCImageBuilder(void);

	void DrawImage(std::string imagePath, VCRectangle frame, float depthStep);
	void Draw9SliceImage(std::string imagePath, VCRectangle frame, int pizelOffset, float padding, float depthStep);

public:
	VCShader* Shader;

private:
	typedef std::unordered_map<std::string, VCImageInstance*> ImageInstMap;
	ImageInstMap m_imageInstances;
};