////
////  VCMesh.cpp
////  VoxelCraft
////
////  Created by Alec Thilenius on 12/22/2013.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
#include "stdafx.h"
//#include "VCMesh.h"
//
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include "assimp/scene.h"
//
//
//Mesh::MeshEntry::MeshEntry()
//{
//};
//
//Mesh::MeshEntry::~MeshEntry()
//{
//}
//
//Mesh::Mesh()
//{
//}
//
//
//Mesh::~Mesh()
//{
//}
//
//void Mesh::MeshEntry::Init(std::vector<Vertex>& Vertices,  std::vector<unsigned int>& Indices)
//{
//
//}
//
//bool Mesh::LoadMesh(std::string& Filename)
//{
//	bool Ret = false;
//	Assimp::Importer Importer;
//
//	// Fuuuccckkkkk you for returning const. Ugh, sometimes I hate this language. So stupid...
//	aiScene* pScene = (aiScene*) Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
//
//	if (pScene) 
//	{
//		Ret = InitFromScene(pScene, Filename);
//	}
//	else 
//	{
//		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
//	}
//
//	return Ret;
//}
//
//bool Mesh::InitFromScene(aiScene* pScene, std::string& Filename)
//{  
//	m_Entries.resize(pScene->mNumMeshes);
//
//	// Initialize the meshes in the scene one by one
//	for (unsigned int i = 0 ; i < m_Entries.size() ; i++) 
//	{
//		aiMesh* paiMesh = pScene->mMeshes[i];
//		InitMesh(i, paiMesh);
//	}
//
//	return true;
//}
//
//void Mesh::InitMesh(unsigned int Index, aiMesh* paiMesh)
//{
//	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;
//
//	std::vector<Vertex> Vertices;
//	std::vector<unsigned int> Indices;
//
//	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
//
//	for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
//	{
//		const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
//		const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
//		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
//
//		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
//			glm::vec2(pTexCoord->x, pTexCoord->y),
//			glm::vec3(pNormal->x, pNormal->y, pNormal->z));
//
//		Vertices.push_back(v);
//	}
//
//	for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
//	{
//		const aiFace& Face = paiMesh->mFaces[i];
//		assert(Face.mNumIndices == 3);
//		Indices.push_back(Face.mIndices[0]);
//		Indices.push_back(Face.mIndices[1]);
//		Indices.push_back(Face.mIndices[2]);
//	}
//
//	m_Entries[Index].Init(Vertices, Indices);
//}
//
//void Mesh::Render()
//{
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//	for (unsigned int i = 0 ; i < m_Entries.size() ; i++) 
//	{
//		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VertextVBO);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IndexVBO);
//
//		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;
//
//		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) 
//		{
//			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
//		}
//
//		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
//	}
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//}
