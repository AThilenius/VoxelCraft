//
//  VCGeometryTypes.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGeometryTypes.h"


Point::Point()
{

}

Point::Point( int x, int y ) : X(x), Y(y)
{

}

Rectangle::Rectangle()
{

}

Rectangle::Rectangle( int x, int y, int width, int height ) : X(x), Y(y), Width(width), Height(height)
{

}

RectangleF::RectangleF()
{

}

RectangleF::RectangleF( float x, float y, float width, float height ) : X(x), Y(y), Width(width), Height(height)
{

}
