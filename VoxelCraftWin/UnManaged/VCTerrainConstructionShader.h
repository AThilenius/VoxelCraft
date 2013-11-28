//
//  VCTerrainConstructionShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/21/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCShader.h"

class VCTerrainConstructionShader : public VCShader
{
public:
	VCTerrainConstructionShader();
	~VCTerrainConstructionShader(void);

protected:
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PreLink();
	virtual void PostInitialize();
};