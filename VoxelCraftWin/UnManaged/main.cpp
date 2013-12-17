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

int main(int argc, char** argv)
{
	VCApplication app;
    app.Initialize();
	app.EditorMain();
    app.ShutDown();

	return 0;
}