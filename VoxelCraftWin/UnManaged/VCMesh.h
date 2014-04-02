//
//  VCMesh.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/22/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLBuffer;

struct VCStandardVerticie
{
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 BiTangent;

	VCStandardVerticie() {}

	VCStandardVerticie(glm::vec3& pos, glm::vec2& tex, glm::vec3& normal, glm::vec3& tangent, glm::vec3 biTangent) :
		Position(pos),
		UV(tex),
		Normal(normal),
		Tangent(tangent),
		BiTangent(biTangent)
	{
	}
};


class VCMesh
{
public:
	VCMesh();
	~VCMesh();

	void Initialize(VCStandardVerticie* verts, UInt32* indicies, int vCount, int iCount);
	void Render();

public:
	int VertexCount;
	int IndexCount;

private:
	VCGLBuffer* m_gpuBuffer;
};
