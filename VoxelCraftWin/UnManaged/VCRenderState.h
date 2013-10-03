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

#define VC_BATCH_SCENE 20
#define VC_BATCH_GUI_BASE 25
#define VC_BATCH_GUI 30

#define VC_BATCH_MIN 1
#define VC_BATCH_MAX 1000000

class VCRenderState
{
public:
	VCRenderState(void):
		StageCount(1),
		BatchingOrder(VC_BATCH_SCENE)
	{
	}

	~VCRenderState(void)
	{
	}

	int BatchingOrder;
	int StageCount;
	VCRenderStage Stages[MAX_STAGE_COUNT];
};

inline bool operator==(const VCRenderState& lhs, const VCRenderState& rhs)
{
	if (lhs.BatchingOrder != rhs.BatchingOrder || lhs.StageCount != rhs.StageCount)
		return false;

	for ( int i = 0; i < lhs.StageCount; i++ )
		if (lhs.Stages[i] != rhs.Stages[i])
			return false;

	return true;
}
inline bool operator< (const VCRenderState& lhs, const VCRenderState& rhs)
{
	if (lhs.BatchingOrder < rhs.BatchingOrder) return true;
	if (lhs.BatchingOrder > rhs.BatchingOrder) return false;

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
