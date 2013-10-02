//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "Shader.h"

#define MAX_TEXTURES 4

class VCRenderStage
{
public:
	VCRenderStage(void);
	~VCRenderStage(void);

	GLuint FrameBuffer;
	Shader* Shader;
	GLuint Textures[MAX_TEXTURES];
	bool Blend;
	bool DepthTest;
};


inline bool operator==(const VCRenderStage& lhs, const VCRenderStage& rhs)
{
	if (lhs.FrameBuffer != rhs.FrameBuffer)
		return false;

	if (lhs.Shader != rhs.Shader)
		return false;

	for ( int i = 0; i < MAX_TEXTURES; i++ )
		if (lhs.Textures[i] != rhs.Textures[i])
			return false;

	return lhs.Blend == rhs.Blend && lhs.DepthTest == rhs.DepthTest;
}
inline bool operator< (const VCRenderStage& lhs, const VCRenderStage& rhs)
{
	// Order or priority:
	// FrameBuffer
	// Shader
	// Textures
	// Blend / Depth

	if (lhs.FrameBuffer < rhs.FrameBuffer) return true;
	if (lhs.FrameBuffer > rhs.FrameBuffer) return false;

	if (lhs.Shader < rhs.Shader) return true;
	if (lhs.Shader > rhs.Shader) return false;

	for ( int i = 0; i < MAX_TEXTURES; i++ )
	{
		if (lhs.Textures[i] < rhs.Textures[i]) return true;
		if (lhs.Textures[i] > rhs.Textures[i]) return false;
	}

	if (lhs.Blend < rhs.Blend) return true;
	if (lhs.Blend > rhs.Blend) return false;

	if (lhs.DepthTest < rhs.DepthTest) return true;
	if (lhs.DepthTest > rhs.DepthTest) return false;

	return false;
}

inline bool operator!=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator==(lhs,rhs);}
inline bool operator> (const VCRenderStage& lhs, const VCRenderStage& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator< (lhs,rhs);}

struct _VCRenderStageCompare 
{
	bool operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
	{
		return (*lhs) < (*rhs);
	}
};
