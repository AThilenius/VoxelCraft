//
//  VCMesh.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/22/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLBuffer;

struct VCPuvnVerticie
{
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec3 Normal;

	VCPuvnVerticie() {}

	VCPuvnVerticie(glm::vec3& pos, glm::vec2& tex, glm::vec3& normal) :
		Position(pos),
		UV(tex),
		Normal(normal)
	{
	}
};


class VCMesh
{
public:
	VCMesh();
	~VCMesh();

	void Initialize(VCPuvnVerticie* verts, UInt32* indicies, int vCount, int iCount);
	void Render();

public:
	int VertexCount;
	int IndexCount;

private:
	VCGLBuffer* m_gpuBuffer;
};
