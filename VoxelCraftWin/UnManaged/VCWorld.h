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

private:
	int m_viewDistTwo;
	int m_logViewDistTwo;
	VCChunk** m_chunks;
};

// Interop
DLL_EXPORT_API int VCInteropNewWorld();
DLL_EXPORT_API void VCInteropReleaseWorld(int handle);

DLL_EXPORT_API int VCInteropWorldGetCamera(int handle);
DLL_EXPORT_API void VCInteropWorldSetViewDist(int handle, int distance);
DLL_EXPORT_API void VCInteropWorldInitializeEmpty(int handle);
DLL_EXPORT_API void VCInteropWorldRebuild(int handle, VCWorldRebuildParams params);

DLL_EXPORT_API void VCInteropWorldSaveToFile (int handle, char* path);
DLL_EXPORT_API void VCInteropWorldLoadFromFile (int handle, char* path);

DLL_EXPORT_API vcint4 VCInteropWorldGetBlock (int handle, int x, int y, int z );
DLL_EXPORT_API void VCInteropWorldSetBlock (int handle, int x, int y, int z, vcint4 block);
DLL_EXPORT_API int VCInteropWorldRaycast(int handle, Ray ray, RaycastHit* hitOut);