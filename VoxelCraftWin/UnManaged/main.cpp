//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <signal.h>

#include "stdafx.h"
#include "VCCamera.h"
#include "VCApplication.h"

int main(int argc, char** argv)
{
	VCApplication app;
    app.Initialize();
	app.EditorMain();
    app.ShutDown();

	return 0;
}