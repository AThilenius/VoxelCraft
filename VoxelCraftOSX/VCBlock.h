#pragma once

#include "PCH.h"

typedef enum : char
{
	Block_Unknown = 0,
	Block_Air = 1,
	Block_Dirt = 2

} BlockType;

class VCBlock
{
public:
	VCBlock(void);
	~VCBlock(void);

	GLbyte4 GetColor();

	BlockType Type;
};

