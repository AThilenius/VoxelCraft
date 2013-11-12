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
#include "VCApplication.h"

#include "delegate.hpp"

// Sample Delegate Usage
//typedef srutil::delegate2<void, int, int> TestDelegate;
//TestClass obj;

//test(TestDelegate());
//test(TestDelegate::from_function<&f>());
//test(TestDelegate::from_method<TestClass, &TestClass::m1>(&obj));
//test(TestDelegate::from_const_method<TestClass, &TestClass::m2>(&obj));
//test(TestDelegate::from_function<&TestClass::m3>());

int main(int argc, char** argv)
{
	VCApplication app;
    app.Initialize();
	app.EditorMain();
    app.ShutDown();

	return 0;
}