//
//  VCLog.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/13/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCLog.h"

LogGeneralHandlers VCLog::ManageHandler = NULL;


VCLog::VCLog(void)
{
}


VCLog::~VCLog(void)
{
}

void VCLog::Info( std::string message, std::string catagory /*= "Default"*/ )
{
	ManageHandler(0, (char*) catagory.c_str(), (char*) message.c_str());
}

void VCLog::Warning( std::string message, std::string catagory /*= "Default"*/ )
{
	ManageHandler(1, (char*) catagory.c_str(), (char*) message.c_str());
}

void VCLog::Error( std::string message, std::string catagory /*= "Default"*/ )
{
	ManageHandler(2, (char*) catagory.c_str(), (char*) message.c_str());
}

void VCInteropLogRegisterManagedHooks(LogGeneralHandlers handler)
{
	VCLog::ManageHandler = handler;
}
