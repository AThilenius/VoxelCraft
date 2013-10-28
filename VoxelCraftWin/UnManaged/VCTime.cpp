//
//  VCTime.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include <Windows.h>
#include "VCTime.h"

VCTime* VCTime::Instance;
float VCTime::CurrentTime;
float VCTime::DeltaTime;

INT64 vctime_tickFrequancy = 0;
double vctime_ticksPerSecond = 0;
INT64 vctime_startTicks = 0;
INT64 vctime_lastTime = 0;

VCTime::VCTime(void)
{
    VCTime::Instance = this;
}


VCTime::~VCTime(void)
{
}

void VCTime::Initalize()
{
    //vctime_startTime = boost::posix_time::microsec_clock::local_time();
    //vctime_lastFrameTime = boost::posix_time::microsec_clock::local_time();
	LARGE_INTEGER li;

    QueryPerformanceFrequency(&li);
	vctime_tickFrequancy = li.QuadPart;
	vctime_ticksPerSecond = (double)(vctime_tickFrequancy);

	QueryPerformanceCounter(&li);
	vctime_startTicks = li.QuadPart;
	vctime_lastTime = vctime_startTicks;

    std::cout << "VCTime Initialized [ " << (int)vctime_ticksPerSecond << " T/S ]" << std::endl;
}

void VCTime::Update()
{
    //boost::posix_time::ptime currentTime = boost::posix_time::microsec_clock::local_time();
    //boost::posix_time::time_duration delta = currentTime - vctime_lastFrameTime;
    //
    //vctime_deltaTime = delta.total_microseconds() / 1000000.0f;
    //
    //vctime_lastFrameTime = currentTime;
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);
	INT64 newCurrentTime = li.QuadPart;

	VCTime::DeltaTime = (float)((double)(newCurrentTime - vctime_lastTime) / vctime_ticksPerSecond);
	VCTime::CurrentTime = (float)((double)(newCurrentTime - vctime_startTicks) / vctime_ticksPerSecond);

	vctime_lastTime = newCurrentTime;
}

//double VCTime::CurrentTime()
//{   
//    boost::posix_time::ptime currentTime = boost::posix_time::microsec_clock::local_time();
//    boost::posix_time::time_duration delta = currentTime - VCTime::Instance->vctime_startTime;
//    
//    return delta.total_microseconds() / 1000000.0f;
//
//	return 1.01f;
//}
//
//double VCTime::DeltaTime()
//{
//    return VCTime::Instance->vctime_deltaTime;
//
//	return 0.01f;
//}
