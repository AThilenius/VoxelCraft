//
//  AssimpBindings.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 4/23/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "AssimpBindings.h"
#include <assimp/cimport.h>
#include "assimp/postprocess.h"
#include "assimp/scene.h"


void* VCIneteropAssimpLoadScene( char* fullPath, int loadFlags, int* meshCount )
{
	// Documentation says I shouldn't remove the const with a cast,
	// I told the documentation to suck a...
	aiScene* pScene = (aiScene*) aiImportFile (fullPath, loadFlags);
	  /*aiProcess_GenSmoothNormals		 |
		aiProcess_CalcTangentSpace       | 
		aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices  |
		aiProcess_SortByPType			 |
		aiProcess_FlipUVs);*/

	if (!pScene)
	{
		VCLog::Error("Failed to parse " + std::string(fullPath), "Resources");
		return NULL;
	}

	*meshCount = pScene->mNumMeshes;

	return pScene;
}

void VCInteropAssimpGetMeshMeta( void* scene, int meshId, int* vertCount, int* facesCount, int* animMeshesCount, int* bonesCount )
{
	aiScene* pScene = (aiScene*) scene;
	aiMesh* paiMesh = pScene->mMeshes[meshId];

	*vertCount = paiMesh->mNumVertices;
	*facesCount = paiMesh->mNumFaces;
	*animMeshesCount = paiMesh->mNumAnimMeshes;
	*bonesCount = paiMesh->mNumBones;
}

void VCInteropAssimpGetMeshData( void* scene, int meshId, VCStandardVerticie* vertBuffer, void* indexBuffer )
{
	aiScene* pScene = (aiScene*) scene;
	aiMesh* paiMesh = pScene->mMeshes[meshId];

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
	{
		const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mTangents[i]) : &Zero3D;
		const aiVector3D* pBiTangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero3D;

		vertBuffer[i] = VCStandardVerticie(
			glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z),
			glm::vec3(pTangent->x, pTangent->x, pTangent->x),
			glm::vec3(pBiTangent->x, pBiTangent->x, pBiTangent->x));
	}

	UInt32 neededIndeciesCount = paiMesh->mNumFaces * 3;

	// Fits UByte
	if ( neededIndeciesCount <= ( 1 << 8 ) )
	{
		UInt8* iBuffer = (UInt8*) indexBuffer;

		for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);

			iBuffer[i * 3 + 0] = (UInt8) Face.mIndices[0];
			iBuffer[i * 3 + 1] = (UInt8) Face.mIndices[1];
			iBuffer[i * 3 + 2] = (UInt8) Face.mIndices[2];
		}
	}

	// Fits UShort
	else if ( neededIndeciesCount <= ( 1 << 16 ) )
	{
		UInt16* iBuffer = (UInt16*) indexBuffer;

		for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);

			iBuffer[i * 3 + 0] = (UInt16) Face.mIndices[0];
			iBuffer[i * 3 + 1] = (UInt16) Face.mIndices[1];
			iBuffer[i * 3 + 2] = (UInt16) Face.mIndices[2];
		}
	}

	// Fits UInt
	else if ( neededIndeciesCount <= ( 1 << 32 ) )
	{
		VCLog::Warning(neededIndeciesCount + " is an excessive number of verts for a single model. Consider splitting the model.", "Resources");

		UInt32* iBuffer = (UInt32*) indexBuffer;

		for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);

			iBuffer[i * 3 + 0] = (UInt32) Face.mIndices[0];
			iBuffer[i * 3 + 1] = (UInt32) Face.mIndices[1];
			iBuffer[i * 3 + 2] = (UInt32) Face.mIndices[2];
		}
	}

	else
	{
		VCLog::Error("There can't possibly be more than 2^32 indecies... something is fucked up.", "Resources");
	}
	
}

void VCInteropAssimpFreeScene( void* scene )
{
	aiScene* pScene = (aiScene*) scene;
	aiReleaseImport(pScene);
}

