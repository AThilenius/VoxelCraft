//
//  VCResourceManager.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCShader;

class VCResourceManager
{
public:
	VCResourceManager();
	~VCResourceManager();

	static VCShader* GetShader (std::string& path);
	
};
