////
////  VCMeshSection.h
////  VoxelCraft
////
////  Created by Alec Thilenius on 12/23/2013.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
//#pragma once
//#include "VCPoolableResource.h"
//
//struct VCPuvnVerticie
//{
//	glm::vec3 Position;
//	glm::vec2 UV;
//	glm::vec3 Normal;
//
//	VCPuvnVerticie() {}
//
//	VCPuvnVerticie(glm::vec3& pos, glm::vec2& tex, glm::vec3& normal) :
//		Position(pos),
//		UV(tex),
//		Normal(normal)
//	{
//	}
//};
//
//class VCMeshSection : public VCPoolableResource<VCMeshSection, 
//{
//public:
//	VCMeshSection();
//	~VCMeshSection();
//
//	void Initialize(VCPuvnVerticie* verts, UInt32* indicies, int vCount, int iCount);
//
//private:
//	void Render();
//
//public:
//	int VertexCount;
//	int IndexCount;
//
//private:
//	GLuint m_VAO;
//	GLuint m_vertextVBO;
//	GLuint m_indexVBO;
//	
//};
