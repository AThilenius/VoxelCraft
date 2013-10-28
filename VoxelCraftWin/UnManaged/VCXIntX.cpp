//
//  VCXIntX.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCXIntX.h"

vcint2::vcint2() : X(0), Y(0)
{

}

vcint2::vcint2( int x, int y ) : X(x), Y(y)
{

}

vcint3::vcint3() : X(0), Y(0), Z(0)
{

}

vcint3::vcint3( int x, int y, int z ) : X(x), Y(y), Z(z)
{

}

vcint4::vcint4() : X(0), Y(0), Z(0), W(0)
{

}

vcint4::vcint4( int x, int y, int z, int w ) : X(x), Y(y), Z(z), W(w)
{

}
