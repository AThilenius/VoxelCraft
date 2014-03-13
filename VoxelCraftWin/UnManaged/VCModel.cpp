//
//  VCModel.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/26/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCModel.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "VCGLShader.h"
#include "VCCamera.h"


std::unordered_map<std::string, VCModel*> VCModel::m_loadedModels;


VCModel::VCModel(void)
{
}


VCModel::~VCModel(void)
{
}

VCModel* VCModel::GetModel(std::string& Filename)
{
	auto itor = m_loadedModels.find(Filename);

	if (itor != m_loadedModels.end())
		return itor->second;

	bool Ret = false;
	Assimp::Importer Importer;

	// Fffffuuuccckkkkk you for returning const. Ugh, sometimes I hate this language. So stupid...
	aiScene* pScene = (aiScene*) Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (!pScene)
	{
		VC_ERROR("Failed to parse " << Filename);
	}

	// Pre-alloc
	VCModel* model = new VCModel();
	model->Meshes.resize(pScene->mNumMeshes);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0 ; i < model->Meshes.size() ; i++)
	{
		aiMesh* paiMesh = pScene->mMeshes[i];

		std::vector<VCPuvnVerticie> Vertices;
		std::vector<UInt32> Indices;

		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
		{
			const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

			Vertices.push_back(VCPuvnVerticie(
				glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z)));
		}

		for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
		}

		model->Meshes[i].Initialize(&Vertices[0], &Indices[0], Vertices.size(), Indices.size());
	}

	m_loadedModels.insert(std::unordered_map<std::string, VCModel*>::value_type(Filename, model));

	return model;
}