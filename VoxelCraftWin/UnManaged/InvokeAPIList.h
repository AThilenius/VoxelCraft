//
//  CallbackAPI.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 12/17/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

// DO NOT PRAGMA ONCE

#define VC_COLLAPSED_INVOKE_API \
VC_INVOKE_API(void,EditorEntry,(),());\
VC_INVOKE_API(void,TestWithInt,(int val),(val));