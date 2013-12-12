//
//  VCGuiShader.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCShader.h"

class VCGuiShader : public VCShader
{
public:
	VCGuiShader(void);
	~VCGuiShader(void);

	void SetNoise(float level);

protected:
	virtual void Bind(VCCamera* camera);
	virtual void BindAttribLocations();
	virtual void GetUniformIDs();
	virtual void PostInitialize();

private:
	GLint m_unifProjMatrix;
	GLint m_unifNoiseScaler;
};


