//
//  VCLog.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/13/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

// Managed function pointer signature
typedef void (*LogGeneralHandlers)(int, char*, char*);

class VCLog
{
public:
	static void Notify(std::string message);
	static void Info (std::string message, std::string catagory = "Default");
	static void Warning (std::string message, std::string catagory = "Default");
	static void Error (std::string message, std::string catagory = "Default");

public:
	static LogGeneralHandlers ManageHandler;

private:
	VCLog();
	~VCLog();
};

DLL_EXPORT_API void VCInteropLogRegisterManagedHooks(LogGeneralHandlers handler);