//
//  VCCursor.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 12/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct CursorType
{
	enum Type
	{
		AppStarting,
		Normal,
		Cross,
		Hand,
		Help,
		IBeam,
		No,
		SizeAll,
		SizeNESW,
		SizeNS,
		SizeNWSE,
		SizeWE,
		Up,
		Wait
	};
};

class VCCursor
{
public:
	VCCursor(void);
	~VCCursor(void);

	void Initialize();
	void SetCursorIcon(CursorType::Type ctype);
};

