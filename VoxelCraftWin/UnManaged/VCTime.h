//
//  VCTime.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
//#include "boost/date_time/posix_time/posix_time.hpp"

class VCTime
{
public:
	VCTime(void);
	~VCTime(void);
    
    void Initalize();
    void Update();

	static float CurrentTime;
    static float DeltaTime;
    
    static VCTime* Instance;
    
private:

    //boost::posix_time::ptime m_startTime;
    //boost::posix_time::ptime m_lastFrameTime;

};

