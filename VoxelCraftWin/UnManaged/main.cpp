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


#include "VCApplication.h"

int main(int argc, char** argv)
{
	//std::ofstream out("VCDebugLog.txt");
	//std::cout.rdbuf(out.rdbuf());
	//std::cerr.rdbuf(out.rdbuf());

	VCApplication app;
    app.Initialize();
	app.EditorMain();
	//app.GameMain();
    app.ShutDown();

	return 0;
}