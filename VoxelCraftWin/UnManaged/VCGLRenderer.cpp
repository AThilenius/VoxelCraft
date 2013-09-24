//
//  VCGLRenderer.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGLRenderer.h"

// Statics
VCVoxelShader* VCGLRenderer::VoxelShader = NULL;


VCGLRenderer::VCGLRenderer(void)
{
	VoxelShader = new VCVoxelShader();
    
    glErrorCheck();
}


VCGLRenderer::~VCGLRenderer(void)
{
}

void VCGLRenderer::Initialize()
{   
	// GL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glErrorCheck();
    
	VoxelShader->Initialize();
    glErrorCheck();
    
    cout << "VCGLRenderer Initalized" << endl;
}

void VCGLRenderer::Render()
{
	glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}