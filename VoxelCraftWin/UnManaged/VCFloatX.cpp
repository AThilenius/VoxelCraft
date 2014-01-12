//
//  VCFloatX.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCFloatX.h"

VCFloat3::VCFloat3() :
	X(0),
	Y(0),
	Z(0)
{
}

VCFloat3::VCFloat3( float x, float y, float z ) :
	X(x),
	Y(y),
	Z(z)
{
}

VCFloat4::VCFloat4() :
	X(0),
	Y(0),
	Z(0),
	W(0)
{
}

VCFloat4::VCFloat4( float x, float y, float z, float w ) :
	X(x),
	Y(y),
	Z(z),
	W(w)
{
}
