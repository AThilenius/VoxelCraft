//
//  VCFloatX.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct VCFloat3
{
	VCFloat3();
	VCFloat3(float x, float y, float z);

	float X;
	float Y;
	float Z;
};

struct VCFloat4
{
	VCFloat4();
	VCFloat4(float x, float y, float z, float w);

	float X;
	float Y;
	float Z;
	float W;
};