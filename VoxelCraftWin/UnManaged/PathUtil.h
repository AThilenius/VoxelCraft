#ifndef __PATH_UTIL_H__
#define __PATH_UTIL_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>

struct PathUtil
{
	static std::string GetBinDirectory()
	{
		TCHAR path[2048];
		GetModuleFileName( NULL, path, 2048 );

		std::string sWorkingDirectory(path);
		return sWorkingDirectory.substr(0, sWorkingDirectory.find_last_of("\\")).append("\\");
	}

	static std::string GetMonoDirectory()
	{
		return GetBinDirectory().append("Mono\\");
	}

	static std::string GetLibDirectory()
	{
		return GetMonoDirectory().append("lib\\");
	}

	static std::string GetConfigDirectory()
	{
		return GetMonoDirectory().append("etc\\");
	}
};

#endif //__PATH_UTIL_H__