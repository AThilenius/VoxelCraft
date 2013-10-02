//
//  VCRenderState.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCRenderStage.h"

#define MAX_STAGE_COUNT 4

class VCRenderState
{
public:
	VCRenderState(void);
	~VCRenderState(void);

	int StageCount;
	VCRenderStage Stages[MAX_STAGE_COUNT];
};

inline bool operator==(const VCRenderState& lhs, const VCRenderState& rhs)
{
	if (lhs.StageCount != rhs.StageCount)
		return false;

	for ( int i = 0; i < lhs.StageCount; i++ )
		if (lhs.Stages[i] != rhs.Stages[i])
			return false;

	return true;
}
inline bool operator< (const VCRenderState& lhs, const VCRenderState& rhs)
{
	if (lhs.StageCount < rhs.StageCount) return true;
	if (lhs.StageCount > rhs.StageCount) return false;

	for ( int i = 0; i < lhs.StageCount; i++ )
	{
		if (lhs.Stages[i] < rhs.Stages[i]) return true;
		if (rhs.Stages[i] > rhs.Stages[i]) return false;
	}

	return false;
}

inline bool operator!=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator==(lhs,rhs);}
inline bool operator> (const VCRenderState& lhs, const VCRenderState& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator< (lhs,rhs);}

struct _VCRenderStateCompare 
{
	bool operator() (const VCRenderState* lhs, const VCRenderState* rhs) const
	{
		return (*lhs) < (*rhs);
	}
};