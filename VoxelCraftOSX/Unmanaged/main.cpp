//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#import "VCApplication.h"

int main(int argc, char** argv)
{
	VCApplication app;
	app.Initialize(argc, argv);
	app.Run();
    
	return 0;
}