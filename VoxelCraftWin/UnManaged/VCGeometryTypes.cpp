//
//  VCGeometryTypes.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/27/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGeometryTypes.h"


VCPoint::VCPoint()
{

}

VCPoint::VCPoint( int x, int y ) : X(x), Y(y)
{

}

VCRectangle::VCRectangle()
{

}

VCRectangle::VCRectangle( int x, int y, int width, int height ) : X(x), Y(y), Width(width), Height(height)
{

}

VCRectangleF::VCRectangleF()
{

}

VCRectangleF::VCRectangleF( float x, float y, float width, float height ) : X(x), Y(y), Width(width), Height(height)
{

}
