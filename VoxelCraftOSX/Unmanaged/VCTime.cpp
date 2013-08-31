//
//  VCTime.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCTime.h"

VCTime* VCTime::Instance;

VCTime::VCTime(void)
{
    VCTime::Instance = this;
    m_deltaTime = 0.1f;
}


VCTime::~VCTime(void)
{
}

void VCTime::Initalize()
{
    m_startTime = boost::posix_time::microsec_clock::local_time();
    m_lastFrameTime = boost::posix_time::microsec_clock::local_time();
    
    cout << "VCTime Initalized" << endl;
}

void VCTime::Update()
{
    boost::posix_time::ptime currentTime = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration delta = currentTime - VCTime::Instance->m_lastFrameTime;
    
    m_deltaTime = delta.total_milliseconds() * 0.001f;
    
    m_lastFrameTime = currentTime;
}

double VCTime::CurrentTime()
{   
    boost::posix_time::ptime currentTime = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration delta = currentTime - VCTime::Instance->m_startTime;
    
    return delta.total_milliseconds() * 0.001f;
}

double VCTime::DeltaTime()
{
    return VCTime::Instance->m_deltaTime;
}
