//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class Shader;

#include <vector>

class VCRenderStage
{
public:
	VCRenderStage(void);
	~VCRenderStage(void);

public:
	GLuint FrameBuffer;
	Shader* Shader;
	std::vector<VCTexturePtr> Textures;
	VCRectangle Viewport;
	bool Fullscreen;
	bool Blend;
	bool DepthTest;
};

bool operator==(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator< (const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator!=(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator> (const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator<=(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator>=(const VCRenderStage& lhs, const VCRenderStage& rhs);

struct _VCRenderStageCompare 
{
	bool operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const;
};
