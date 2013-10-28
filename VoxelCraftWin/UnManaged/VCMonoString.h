//
//  VCMonoString.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/26/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

typedef void* VCMonoStringPtr;

class VCMonoString
{
public:
	VCMonoString(VCMonoStringPtr monoString);
	~VCMonoString(void);

	static VCMonoStringPtr MakeString (const char* text);
	operator std::string() { return std::string(m_charStar); }
	operator char*() { return m_charStar; }

private:
	char* m_charStar;
};