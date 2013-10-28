//
//  VCPhysics.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/28/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPhysics.h"

Ray::Ray()
{

}

Ray::Ray( glm::vec3 origin, glm::vec3 direction, float maxDist ) : Origin(origin), Direction(direction), MaxDistance(maxDist)
{

}
