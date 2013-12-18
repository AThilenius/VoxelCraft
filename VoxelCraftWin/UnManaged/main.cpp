//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCApplication.h"

// Debug:
#include "VCInteropInvoke.h"

#include "delegate.hpp"

extern "C" __declspec(dllexport) void TestPInvoke();

void TestPInvoke()
{
	//std::cout << "UnManaged Code! PInvoked" << std::endl;
	printf("UnManaged Code! PInvoked");
}

int main(int argc, char** argv)
{
	VCApplication app;
    app.Initialize();
	app.EditorMain();
    app.ShutDown();

	std::cin.ignore();
	return 0;
}