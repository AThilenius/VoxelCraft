//
//  VCWorld.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define FLATTEN_WORLD(X,Y,Z) ((((Z << m_logViewDistTwo) + X) << m_logViewDistTwo ) + Y)
#define WORLD_ORDERED_ITTORATOR(xName,yName,zName) for ( int z = 0; z < m_viewDistTwo; z++ ) { int zName = ChunkZeroZ + z; for ( int x = 0; x < m_viewDistTwo; x++ ) { int xName = ChunkZeroX + x; for ( int y = 0; y < m_viewDistTwo; y++ ) { int yName = ChunkZeroY + y;

class VCBlock;
class VCWorld;
class VCChunk;
class VCIChunkGenerator;
class VCRenderState;
class VCCamera;
struct Ray;
struct RaycastHit;
struct VCInteropBlock;

#include "VCMarshalableObject.h"
#include "VCMonoString.h"

struct VCEditorFileHeader001
{
	int ChunkWidth;
	int WorldSizeX, WorldSizeY, WorldSizeZ;
	int ChunkZeroX, ChunkZeroY, ChunkZeroZ;
};

struct VCWorldRebuildParams
{
	bool ShowShadows;
	bool ForceRebuildAll;
};

class VCWorld : public VCMarshalableObject
{
public:
	VCWorld();
	~VCWorld(void);

	void InitializeEmpty();
	void GenerateRegenerate();
	void Rebuild(VCWorldRebuildParams params);

	void SetViewDistance(int viewDistTwo);

	VCBlock GetBlock ( int x, int y, int z );
	void SetBlock ( int x, int y, int z, VCBlock block );

	// ===== Serialization ================================================
	void Save (std::ofstream& stream);
	void Load (std::ifstream& stream);
	
	// ===== Physics ======================================================
	void GetWorldBounds ( glm::vec3* lower, glm::vec3* upper );
	bool RaycastWorld(Ray ray, RaycastHit* hit);

public:
	VCCamera* Camera;
	int ChunkZeroX, ChunkZeroY, ChunkZeroZ;
	VCIChunkGenerator* ChunkGenerator;

private:
	int m_viewDistTwo;
	int m_logViewDistTwo;
	VCChunk** m_chunks;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();

	// ===============================================================
};

// Interop
int VCInteropNewWorld();
void VCInteropReleaseWorld(int handle);

int VCInteropWorldGetCamera(int handle);
void VCInteropWorldSetGenerator(int wHandle, int cHandle);
void VCInteropWorldSetViewDist(int handle, int distance);
void VCInteropWorldInitializeEmpty(int handle);
void VCInteropWorldGenerateRegenerate(int handle);
void VCInteropWorldRebuild(int handle, VCWorldRebuildParams params);

void VCInteropWorldSaveToFile (int handle, VCMonoStringPtr path);
void VCInteropWorldLoadFromFile (int handle, VCMonoStringPtr path);

VCInteropBlock VCInteropWorldGetBlock (int handle, int x, int y, int z );
void VCInteropWorldSetBlock (int handle, int x, int y, int z, VCInteropBlock block);
int VCInteropWorldRaycast(int handle, Ray ray, RaycastHit* hitOut);