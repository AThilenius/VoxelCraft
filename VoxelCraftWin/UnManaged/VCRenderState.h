//
//  VCRenderState.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCRenderStage.h"

#define VC_BATCH_SCENE 20
#define VC_BATCH_GUI_BASE 25
#define VC_BATCH_GUI 30
#define VC_BATCH_MIN 1
#define VC_BATCH_MAX 1000000

class VCRenderState
{
public:
	VCRenderState(int stageCount);
	~VCRenderState(void);

	int BatchingOrder;
	int StageCount;
	VCRenderStage* Stages;
};

bool operator==(const VCRenderState& lhs, const VCRenderState& rhs);
bool operator< (const VCRenderState& lhs, const VCRenderState& rhs);
bool operator!=(const VCRenderState& lhs, const VCRenderState& rhs);
bool operator> (const VCRenderState& lhs, const VCRenderState& rhs);
bool operator<=(const VCRenderState& lhs, const VCRenderState& rhs);
bool operator>=(const VCRenderState& lhs, const VCRenderState& rhs);

struct _VCRenderStateCompare 
{
	bool operator() (const VCRenderState* lhs, const VCRenderState* rhs) const;
};
