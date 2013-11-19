//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCRenderStage;

#include "VCShader.h"

typedef std::shared_ptr<VCRenderStage> VCRenderStagePtr;

class VCRenderStage
{
public:
	~VCRenderStage(void);
	//VCRenderStagePtr Create (Shader* shader); 
	//VCRenderStagePtr Create (Shader* shader, std::vector<VCTexturePtr> textures);
	//VCRenderStagePtr Create (Shader* shader, std::vector<VCTexturePtr> textures, GLuint frameBuffer);
	//VCRenderStagePtr Create (Shader* shader, std::vector<VCTexturePtr> textures, GLuint frameBuffer, bool blend, bool depthTest);

//private:
	VCRenderStage(void);

public:
	UInt64 ID;
	GLuint FrameBuffer;
	VCShader* Shader;
	std::vector<VCTexturePtr> Textures;
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
