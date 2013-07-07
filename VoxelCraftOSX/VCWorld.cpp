#include "VCWorld.h"

#include "VCChunk.h"
#include "VCBlock.h"

VCWorld::VCWorld( int viewDistance )
{
	if (((viewDistance - 1) & viewDistance))
		cout << "View distance must be a power of two!" << endl;

	m_viewDist = viewDistance;
	m_logViewDist = log(viewDistance) / log(2);

	m_c0x = m_c0y = m_c0z = 0;
}

VCWorld::~VCWorld(void)
{
}

void VCWorld::Initialize()
{
	m_chunks = (VCChunk**) malloc ( sizeof(VCChunk*) * m_viewDist * m_viewDist * m_viewDist );
	
	m_c0x = 0;
	m_c0y = 0;
	m_c0z = 0;

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)] = new VCChunk(X, Y, Z, this);
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->Generate();
	}}};

	WORLD_ORDERED_ITTORATOR(X,Y,Z)
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->StartRebuild();
		m_chunks[FLATTEN_WORLD(X,Y,Z)]->ContinueRebuild(1000.0f);
	}}};
}

BlockType VCWorld::GetBlock( int x, int y, int z )
{
	// What chunk?
	int cx = (x >> LOG_CHUNK_WIDTH) - m_c0x;
	int cy = (y >> LOG_CHUNK_WIDTH) - m_c0y;
	int cz = (z >> LOG_CHUNK_WIDTH) - m_c0z;

	// Out of range?
	if (cx < 0 || cx >= m_viewDist * 2)
		return Block_Unknown;

	if (cy < 0 || cy >= m_viewDist * 2)
	    return Block_Unknown;

	if (cz < 0 || cz >= m_viewDist * 2)
		return Block_Unknown;

	VCChunk* chunk = m_chunks[FLATTEN_WORLD(cx, cy, cz)];

	// Where in chunk?
	int lx = x & MASK_CHUNK_WIDTH;
	int ly = y & MASK_CHUNK_WIDTH;
	int lz = z & MASK_CHUNK_WIDTH;

	return chunk->GetBlock(lx, ly, lz);
}
