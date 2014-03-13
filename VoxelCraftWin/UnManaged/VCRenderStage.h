//
//  VCRenderStage.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

// Key Bit-Layout:
// 0      -4-      4      -4-      8      -4-      12       -8-       20             -16-            36  -1-  37  -1-  38              -26-              64
// |===============|===============|===============|==================|==============================|========|========|=================================|
// | BatchingOrder |  StageOrder   |      FBO      |      Shader      |            Texture           | Blend  | DepthT |          Not Yet Used           |
// |===============|===============|===============|==================|==============================|========|========|=================================|

#pragma once

#define VC_BATH_DEFAULT 2
#define VC_BATCH_SCENE 2
#define VC_BATCH_GUI_BASE 5
#define VC_BATCH_GUI 6
#define VC_BATCH_MIN 1
#define VC_BATCH_MAX 16

class VCRenderStage;
class VCGLTexture;

#include "VCGLShader.h"

class VCRenderStage
{
public:
	VCRenderStage(VCVoidDelegate function);
	~VCRenderStage(void);
	void BuildKey();

	// Sets all delta-states and executes the bound function.
	static void TransitionAndExecute(VCRenderStage* fromState, VCRenderStage* toState);

public:
	UInt64 Key;

	// Compared in descending sort order:
	int BatchOrder;
	int StageOrder;
	GLuint FrameBuffer;
	VCGLShader* Shader;
	VCGLTexture* Texture;
	bool Blend;
	bool DepthTest;
	VCVoidDelegate ExecutionFunction;

	// Not Compared
	enum ExecutionTypes { Always, Once, Never };
	ExecutionTypes ExectionType;
	VCCamera* Camera;
};

bool operator==(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator< (const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator!=(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator> (const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator<=(const VCRenderStage& lhs, const VCRenderStage& rhs);
bool operator>=(const VCRenderStage& lhs, const VCRenderStage& rhs);
