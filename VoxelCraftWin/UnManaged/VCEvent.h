//
//  VCEvent.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/11/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once


class VCEvent
{
public:
	VCEvent(void);
	~VCEvent(void);

	//boost::signals::connection operator+= (const boost::signal<void (void*, void*)>::slot_type& handler);
	//void operator() (void* sender, void* args);

private:
	//std::vector<FastDelegate2<void*, VCEventArgs*>> m_delegates;
};