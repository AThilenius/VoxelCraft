//
//  VCBlock.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCBlock.h"

VCBlock VCBlock::ErrorBlock = VCBlock(255, 0, 0, 255);
VCBlock VCBlock::Air = VCBlock(0, 0, 0, 0);

VCBlock::VCBlock( void )
{

}

VCBlock::VCBlock( vcint4 interopBlock ) : Color((GLubyte) interopBlock.X, (GLubyte) interopBlock.Y, (GLubyte) interopBlock.Z, (GLubyte) interopBlock.W)
{

}

VCBlock::VCBlock( GLubyte r, GLubyte g, GLubyte b ) : Color(GLubyte4(r, g, b, 255))
{

}

VCBlock::VCBlock( GLubyte r, GLubyte g, GLubyte b, GLubyte a ) : Color(GLubyte4(r, g, b, a))
{

}

VCBlock::~VCBlock( void )
{

}

bool VCBlock::IsTrasparent()
{
	return Color.w == 0;
}

bool VCBlock::IsTranslucent()
{
	return Color.w != 255;
}

bool VCBlock::IsSolid()
{
	return Color.w == 255;
}

vcint4 VCBlock::AsInterop()
{
	return vcint4(Color.x, Color.y, Color.z, Color.w);
}
