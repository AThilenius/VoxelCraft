//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCGame.h"

int main(int argc, char** argv)
{
	VCGame game;
    game.Initalize();
    game.Run();
    game.ShutDown();
    
	return 0;
}