//
//  main.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#import "VCApplication.h"
#import "VCTestApplication.h"

int main(void)
{
	VCApplication app;
	app.Initialize();
	app.Run();
    
//    VCTestApplication* m_testApp = new VCTestApplication();
//    m_testApp->Initialize();
//    m_testApp->Run();

	return 0;
}