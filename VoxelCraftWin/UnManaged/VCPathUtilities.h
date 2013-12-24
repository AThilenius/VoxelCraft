//
//  VCPathUtilities.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCPathUtilities
{
public:
	static std::string Combine(std::string path, std::string path2);

public:
	static std::string VCResourcePath;
	static std::string VCFontsPath;
	static std::string VCImagesPath;
	static std::string VCShadersPath;
	static std::string VCLoadersPath;
	static std::string VCBMFontPath;
	static std::string VCAssetsPath;
	static std::string VCMeshesPath;

private:
	VCPathUtilities(){}
	~VCPathUtilities(){}
};

DLL_EXPORT_API void VCInteropPathSetPath( int id, char* path );