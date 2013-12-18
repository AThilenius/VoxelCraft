//
//  VC3DLineDrawer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/29/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define MAX_LINE_COUNT 1000000

class VCRenderStage;
class VCCamera;

#include "VCMarshalableObject.h"

struct LineVerticie
{
	LineVerticie();
	LineVerticie(glm::vec3 position, GLubyte4 color);

	glm::vec3 Position;
	GLubyte4 Color;
};

class VC3DLineDrawer : public VCMarshalableObject
{
public:
	VC3DLineDrawer(VCCamera* camera);
	~VC3DLineDrawer(void);
	void Initialize();
	void DrawLine (glm::vec3 from, glm::vec3 to, GLubyte4 color);

private:
	void Render();

private:
	VCRenderStage* m_renderStage;
	VCCamera* m_camera;
	bool m_warningIssued;
	int m_lineVertCount;
	GLuint m_VAO;
	GLuint m_VBO;
	LineVerticie m_lineVerts[MAX_LINE_COUNT];
};

// Interop
DLL_EXPORT_API int VCInteropNew3DLineDrawer(int cameraHandle);
DLL_EXPORT_API void VCInteropRelease3DLineDrawer(int handle);
DLL_EXPORT_API void VCInterop3DLineDrawerDrawLine (int handle, glm::vec3 from, glm::vec3 to, vcint4 color);