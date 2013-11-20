//
//  VCRenderState.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCRenderState.h"

//VCRenderState::VCRenderState(int stageCount):
//	StageCount(stageCount),
//	BatchingOrder(VC_BATCH_SCENE),
//	Camera(NULL)
//{
//	Stages = new VCRenderStage[stageCount];
//}
//
//VCRenderState::~VCRenderState( void )
//{
//	delete[] Stages;
//}
//
//bool _VCRenderStateCompare::operator() (const VCRenderState* lhs, const VCRenderState* rhs) const
//{
//	return (*lhs) < (*rhs);
//}
//
//bool operator==(const VCRenderState& lhs, const VCRenderState& rhs)
//{
//	if (lhs.BatchingOrder != rhs.BatchingOrder || lhs.StageCount != rhs.StageCount || lhs.Camera != rhs.Camera)
//		return false;
//
//	for ( int i = 0; i < lhs.StageCount; i++ )
//		if (lhs.Stages[i] != rhs.Stages[i])
//			return false;
//
//	return true;
//}
//bool operator< (const VCRenderState& lhs, const VCRenderState& rhs)
//{
//	if (lhs.BatchingOrder < rhs.BatchingOrder) return true;
//	if (lhs.BatchingOrder > rhs.BatchingOrder) return false;
//
//	if (lhs.StageCount < rhs.StageCount) return true;
//	if (lhs.StageCount > rhs.StageCount) return false;
//
//	for ( int i = 0; i < lhs.StageCount; i++ )
//	{
//		if (lhs.Stages[i] < rhs.Stages[i]) return true;
//		if (rhs.Stages[i] > rhs.Stages[i]) return false;
//	}
//
//	// Arbitrary camera compare ( Add layer order here later )
//	return lhs.Camera < rhs.Camera;
//}
//
//bool operator!=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator==(lhs,rhs);}
//bool operator> (const VCRenderState& lhs, const VCRenderState& rhs){return  operator< (rhs,lhs);}
//bool operator<=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator> (lhs,rhs);}
//bool operator>=(const VCRenderState& lhs, const VCRenderState& rhs){return !operator< (lhs,rhs);}