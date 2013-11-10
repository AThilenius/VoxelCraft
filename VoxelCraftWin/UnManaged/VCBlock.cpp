//
//  VCBlock.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCBlock.h"

VCInteropBlock::VCInteropBlock() : Color(vcint4())
{

}

VCInteropBlock::VCInteropBlock( GLubyte4 color ) : Color(vcint4(color.x, color.y, color.z, color.w))
{

}

VCBlock VCBlock::ErrorBlock = VCBlock(255, 0, 0, 255);
VCBlock VCBlock::Air = VCBlock(0, 0, 0, 0);

VCBlock::VCBlock( void )
{

}

VCBlock::VCBlock( VCInteropBlock interopBlock ) : Color((GLubyte) interopBlock.Color.X, (GLubyte) interopBlock.Color.Y, (GLubyte) interopBlock.Color.Z, (GLubyte) interopBlock.Color.W)
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

VCInteropBlock VCBlock::AsInterop()
{
	return VCInteropBlock(Color);
}
