//
//  VCImageBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCImageInstance;
class VCGLShader;

class VCImageBuilder
{
public:
	VCImageBuilder(void);
	~VCImageBuilder(void);

	void DrawImage(VCGLTexture* tex, VCRectangle frame, float depthStep);
	void Draw9SliceImage(VCGLTexture* tex, VCRectangle frame, int pizelOffset, float padding, float depthStep);

public:
	VCGLShader* Shader;

private:
	typedef std::unordered_map<VCGLTexture*, VCImageInstance*> ImageInstMap;
	ImageInstMap m_imageInstances;
};