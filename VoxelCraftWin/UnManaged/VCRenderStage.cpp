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

VCRenderStage::VCRenderStage(void):
	FrameBuffer(0),
	Shader(NULL),
	Blend(true),
	DepthTest(true)
{
}

VCRenderStage::~VCRenderStage(void)
{
}

//VCRenderStagePtr VCRenderStage::Create( Shader* shader )
//{
//	return Create ( shader, std::vector<VCTexturePtr>(), 0, true, true );
//}
//
//VCRenderStagePtr VCRenderStage::Create( Shader* shader, std::vector<VCTexturePtr> textures )
//{
//	return Create ( shader, textures, 0, true, true );
//}
//
//VCRenderStagePtr VCRenderStage::Create( Shader* shader, std::vector<VCTexturePtr> textures, GLuint frameBuffer )
//{
//	return Create ( shader, textures, frameBuffer, true, true );
//}
//
//VCRenderStagePtr VCRenderStage::Create( Shader* shader, std::vector<VCTexturePtr> textures, GLuint frameBuffer, bool blend, bool depthTest )
//{
//	
//}

bool operator==(const VCRenderStage& lhs, const VCRenderStage& rhs)
{
	if (lhs.FrameBuffer != rhs.FrameBuffer)
		return false;

	if (lhs.Shader != rhs.Shader)
		return false;

	if (lhs.Textures.size() != rhs.Textures.size())
		return false;

	for ( int i = 0; i < lhs.Textures.size(); i++ )
		if (lhs.Textures[i] != rhs.Textures[i])
			return false;

	return lhs.Blend == rhs.Blend && lhs.DepthTest == rhs.DepthTest;
}

bool operator< (const VCRenderStage& lhs, const VCRenderStage& rhs)
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

	if (lhs.Textures.size() < rhs.Textures.size()) return true;
	if (lhs.Textures.size() > rhs.Textures.size()) return false;

	for ( int i = 0; i < lhs.Textures.size(); i++ )
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

bool operator!=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator==(lhs,rhs);}
bool operator> (const VCRenderStage& lhs, const VCRenderStage& rhs){return  operator< (rhs,lhs);}
bool operator<=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator> (lhs,rhs);}
bool operator>=(const VCRenderStage& lhs, const VCRenderStage& rhs){return !operator< (lhs,rhs);}

bool _VCRenderStageCompare::operator() (const VCRenderStage* lhs, const VCRenderStage* rhs) const
{
	return (*lhs) < (*rhs);
}