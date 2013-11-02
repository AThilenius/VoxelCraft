//
//  VCTexture.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCTexture;

typedef std::shared_ptr<VCTexture> VCTexturePtr;

class VCTexture
{
public:
	~VCTexture(void);

	// Factory
	static VCTexturePtr CreateTexture (const char* path, GLenum uMode, GLenum vMode, GLenum minFilter, GLenum magFilter);
	static VCTexturePtr CreateUnfilteredTexture (const char* path);
	static VCTexturePtr CreateTrilinearTexture (const char* path);
	static VCTexturePtr CreateAnsiotropicTexture (const char* path);

	void Bind(int texUnit);
	void SetUVWrapMode ( GLenum uMode, GLenum vMode );
	void SetFilterMode ( GLenum minFilter, GLenum magFilter );

private:
	VCTexture(void);

private:
	static VCTexturePtr m_boundTexture;

	GLuint m_glTextID;
	std::weak_ptr<VCTexture> m_weakPtr;

};
