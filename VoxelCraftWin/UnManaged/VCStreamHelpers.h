//
//  VCStreamHelpers.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

char ReadInt8 ( std::ifstream& f );
short ReadInt16 ( std::ifstream& f );
int ReadInt32 ( std::ifstream& f );
void WriteInt8 ( std::ofstream& f, char value );
void WriteInt16 ( std::ofstream& f, short value );
void WriteInt32 ( std::ofstream& f, int value );