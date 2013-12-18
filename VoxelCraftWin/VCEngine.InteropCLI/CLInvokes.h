#pragma once

using namespace System;
using namespace VCEngine;

#include "InvokeAPIList.h"
#define VC_INVOKE_API(RETURNTYPE,FNAME,ARGS,NAMESONLY) static RETURNTYPE FNAME ARGS { return InteropIn::##FNAME NAMESONLY;  }

ref class CLInvokes
{
public:
	CLInvokes(void){}
	VC_COLLAPSED_INVOKE_API
};

