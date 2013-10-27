//
//  VCMonoString.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/26/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include <string>
#include <memory>

struct _MonoString;

class VCMonoString
{
public:
	VCMonoString(_MonoString* monoString);
	~VCMonoString(void);

	operator std::string() { return m_stdString; }
	operator char*() { return m_charStar; }

private:
	std::string m_stdString;
	char* m_charStar;
};

typedef std::shared_ptr<VCMonoString> VCMonoStrinPtr;
