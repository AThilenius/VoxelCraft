//
//  VCStaticMeshRenderer.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/26/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCStaticMeshRenderer.h"

#include "VCMaterial.h"
#include "VCModel.h"
#include "VCShader.h"
#include "VCCamera.h"


//VCStaticMeshRenderer::VCStaticMeshRenderer(void)
//{
//}
//
//
//VCStaticMeshRenderer::~VCStaticMeshRenderer(void)
//{
//}
//
//void VCStaticMeshRenderer::Render()
//{
//
//	 for (int i = 0; i < Model->Meshes.size(); i++)
//	 {
//		 Materials[i]->Bind();
//		 VCShader::BoundShader->SetMVP(VCCamera::BoundCamera->ProjectionViewMatrix * ModelMatrix);
//		 Model->Meshes[i].Render();
//	 }
//}
