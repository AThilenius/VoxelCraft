//
//  VCMonoString.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/26/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCMonoString.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>

VCMonoString::VCMonoString(_MonoString* monoString)
{
	m_charStar = mono_string_to_utf8(monoString);
	m_stdString = std::string(m_charStar);
}


VCMonoString::~VCMonoString(void)
{
	mono_free(m_charStar);
}