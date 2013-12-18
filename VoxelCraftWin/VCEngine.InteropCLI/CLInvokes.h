#pragma once

using namespace System;
using namespace VCEngine;

ref class CLInvokes
{
public:
	CLInvokes(void);

	static void EditorEntry()
	{
		Editor::EditorMain();
	}


};

