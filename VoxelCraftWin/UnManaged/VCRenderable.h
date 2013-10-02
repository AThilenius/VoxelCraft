//
//  VCRenderable.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCRenderState.h"

class VCRenderable
{
public:
	VCRenderable(void);
	~VCRenderable(void);

	VCRenderState* State;
	GLuint VBO;
	int VertexOffset;
	int VertexCount;
};

inline bool operator==(const VCRenderable& lhs, const VCRenderable& rhs)
{
	return 
		*lhs.State == *rhs.State &&
		lhs.VBO == rhs.VBO &&
		lhs.VertexOffset == rhs.VertexOffset &&
		lhs.VertexCount == rhs.VertexCount;
}

inline bool operator< (const VCRenderable& lhs, const VCRenderable& rhs)
{
	if (*lhs.State < *rhs.State) return true;
	if (*lhs.State > *rhs.State) return false;

	if (lhs.VBO < rhs.VBO) return true;
	if (lhs.VBO > rhs.VBO) return false;

	if (lhs.VertexOffset < rhs.VertexOffset) return true;
	if (lhs.VertexOffset > rhs.VertexOffset) return false;

	if (lhs.VertexCount < rhs.VertexCount) return true;
	if (lhs.VertexCount > rhs.VertexCount) return false;

	return false;
}

inline bool operator!=(const VCRenderable& lhs, const VCRenderable& rhs){return !operator==(lhs,rhs);}
inline bool operator> (const VCRenderable& lhs, const VCRenderable& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const VCRenderable& lhs, const VCRenderable& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const VCRenderable& lhs, const VCRenderable& rhs){return !operator< (lhs,rhs);}

struct _VCRenderableCompare 
{
	bool operator() (const VCRenderable* lhs, const VCRenderable* rhs) const
	{
		return (*lhs) < (*rhs);
	}
};

