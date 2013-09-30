//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "VCGame.h"
#include <signal.h>

int main(int argc, char** argv)
{
	//std::ofstream out("VCDebugLog.txt");
	//std::cout.rdbuf(out.rdbuf());
	//std::cerr.rdbuf(out.rdbuf());

	VCGame game;
    game.Initalize();
    game.Run();
    game.ShutDown();

	return 0;
}