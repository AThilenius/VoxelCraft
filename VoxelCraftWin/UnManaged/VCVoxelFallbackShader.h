////
////  VCVoxelFallbackShader.h
////  VoxelCraftOSX
////
////  Created by Alec Thilenius on 11/29/13.
////  Copyright (c) 2013 Thilenius. All rights reserved.
////
//
//#pragma once
//
//#include "VCShader.h"
//
//class VCVoxelFallbackShader : public VCShader
//{
//public:
//	VCVoxelFallbackShader(void);
//	~VCVoxelFallbackShader(void);
//
//protected:
//	virtual void BindAttribLocations();
//	virtual void GetUniformIDs();
//	virtual void SetModelMatrix( glm::mat4 modelMatrix );
//
//private:
//	GLint m_unifMVP;
//	GLint m_unifViewMatrix;
//	GLint m_unifModelMatrix;
//	GLint m_unifLightInvDirection;
//};