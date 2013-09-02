//
//  VCTransform.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTransform.h"
#import "VCGameObject.h"

/*
VCTransform::VCTransform(VCGameObject* parent) :
    GameObject(parent),
    Position(glm::vec3(0, 0, 0)),
    Rotation(glm::quat()),
    Scale(glm::vec3(1, 1, 1)),
    ModelMatrix(glm::mat4(1.0f))
{
    //Handle = VCObjectStore::Instance->RegisterObject(this);
    //cout << "VCTransform created with handle: " << Handle << endl;
}

VCTransform::~VCTransform(void)
{
    //VCObjectStore::Instance->ReleaseObject(Handle);
}

void VCTransform::PreRender()
{
	// Identity
	ModelMatrix = glm::mat4(1.0f);
    
	if (GameObject->GetParent() != NULL)
		ModelMatrix = GameObject->GetParent()->Transform->ModelMatrix;

    // Rotation
    ModelMatrix = glm::toMat4(Rotation);
    
	// Translation
	ModelMatrix = glm::translate(ModelMatrix, Position);
    
	// Scale
	ModelMatrix = glm::scale(ModelMatrix, Scale.x, Scale.y, Scale.z);	
}
*/