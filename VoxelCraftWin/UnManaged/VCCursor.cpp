//
//  VCCursor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 12/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCCursor.h"

#if defined _WIN32 || defined _WIN64
#include <Windows.h>

HCURSOR g_winCursors[14];
#endif

VCCursor::VCCursor(void)
{

}


VCCursor::~VCCursor(void)
{

}

void VCCursor::Initialize()
{
	// =====   Cursors   ======================================================
#if defined _WIN32 || defined _WIN64
	g_winCursors[0] = LoadCursor(NULL, IDC_APPSTARTING);
	g_winCursors[1] = LoadCursor(NULL, IDC_ARROW);
	g_winCursors[2] = LoadCursor(NULL, IDC_CROSS);
	g_winCursors[3] = LoadCursor(NULL, IDC_HAND);
	g_winCursors[4] = LoadCursor(NULL, IDC_HELP);
	g_winCursors[5] = LoadCursor(NULL, IDC_IBEAM);
	g_winCursors[6] = LoadCursor(NULL, IDC_NO);
	g_winCursors[7] = LoadCursor(NULL, IDC_SIZEALL);
	g_winCursors[8] = LoadCursor(NULL, IDC_SIZENESW);
	g_winCursors[9] = LoadCursor(NULL, IDC_SIZENS);
	g_winCursors[10] = LoadCursor(NULL, IDC_SIZENWSE);
	g_winCursors[11] = LoadCursor(NULL, IDC_SIZEWE);
	g_winCursors[12] = LoadCursor(NULL, IDC_UPARROW);
	g_winCursors[13] = LoadCursor(NULL, IDC_WAIT);
#endif

	SetCursorIcon(CursorType::Cross);
}

void VCCursor::SetCursorIcon( CursorType::Type ctype )
{
#if defined _WIN32 || defined _WIN64
	SetCursor(g_winCursors[(int)ctype]);
#endif
}