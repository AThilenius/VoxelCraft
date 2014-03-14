//
//  VCMesh.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/22/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMesh.h"

#include "VCShadeTypes.h"
#include "VCGLShader.h"
#include "VCGLBuffer.h"


VCMesh::VCMesh():
	m_gpuBuffer(NULL)
{

}

VCMesh::~VCMesh()
{
	SAFE_DELETE(m_gpuBuffer);
}

void VCMesh::Initialize( VCPuvnVerticie* verts, UInt32* indicies, int vCount, int iCount )
{
	VertexCount = vCount;
	IndexCount = iCount;

	m_gpuBuffer = new VCGLBuffer();
	m_gpuBuffer->VertexBufferSpecification()
		.SetVertexAttribute(VCShaderAttribute::Position0,	3, VCGLPrimitives::Float,	false,	sizeof(VCPuvnVerticie),	offsetof(VCPuvnVerticie, Position))
		.SetVertexAttribute(VCShaderAttribute::TexCoord0,	2, VCGLPrimitives::Float,	false,	sizeof(VCPuvnVerticie),	offsetof(VCPuvnVerticie, UV))
		.SetVertexAttribute(VCShaderAttribute::Normal0,		3, VCGLPrimitives::Float,	false,	sizeof(VCPuvnVerticie),	offsetof(VCPuvnVerticie, Normal));
	m_gpuBuffer->IndexBufferSpecification(sizeof(UInt32) * iCount, indicies, iCount);
}

void VCMesh::Render()
{
	// Draw this specific mesh (as a parent of a Model)
	// Possible optimization: Move all children meshes into a single buffer, use [from, to] to draw a part of it.
	m_gpuBuffer->Draw();
}