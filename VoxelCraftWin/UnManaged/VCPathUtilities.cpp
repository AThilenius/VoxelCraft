//
//  VCPathUtilities.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPathUtilities.h"

std::string VCPathUtilities::VCResourcePath;
std::string VCPathUtilities::VCFontsPath;
std::string VCPathUtilities::VCImagesPath;
std::string VCPathUtilities::VCShadersPath;
std::string VCPathUtilities::VCLoadersPath;
std::string VCPathUtilities::VCBMFontPath;
std::string VCPathUtilities::VCAssetsPath;
std::string VCPathUtilities::VCMeshesPath;


void VCInteropPathSetPath( int id, char* path )
{
	switch(id)
	{
	case 0: VCPathUtilities::VCResourcePath = std::string(path); break;
	case 1: VCPathUtilities::VCFontsPath = std::string(path); break;
	case 2: VCPathUtilities::VCImagesPath = std::string(path); break;
	case 3: VCPathUtilities::VCShadersPath = std::string(path); break;
	case 4: VCPathUtilities::VCLoadersPath = std::string(path); break;
	case 5: VCPathUtilities::VCBMFontPath = std::string(path); break;
	case 6: VCPathUtilities::VCAssetsPath = std::string(path); break;
	case 7: VCPathUtilities::VCMeshesPath = std::string(path); break;
	}
}

std::string VCPathUtilities::Combine( std::string path, std::string path2 )
{
	if (path != "" && path[path.length() - 1] == '\\')
		return path + path2;

	else
		return path + "\\" + path2;
}