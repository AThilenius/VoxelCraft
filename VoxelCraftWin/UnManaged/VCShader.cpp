//
//  Shader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCShader.h"

#define VERT_FILE_EXTENSION ".vert"
#define GEOM_FILE_EXTENSION ".geom"
#define FRAG_FILE_EXTENSION ".frag"

VCShader* VCShader::BoundShader = NULL;
VCCamera* VCShader::BoundCamera = NULL;


VCShader::VCShader():
	m_programId(0),
	m_vertexShader(0),
	m_geometryShader(0),
	m_fragShader(0)
{
}

VCShader::~VCShader()
{
	if ( m_programId != 0 )
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}

void VCShader::Initialize()
{
	
	GLuint vertShader = 0;
	GLuint geometryShader = 0;
	GLuint fragShader = 0;
	
    // Create shader program.
	GLuint id = glCreateProgram();
	
	m_programId = id;
    
	// =====   Create and compile shaders   ======================================================
	if (m_vertexShader != NULL)
	{
		std::string literal = LoadTextFile(std::string(m_vertexShader) + VERT_FILE_EXTENSION);
		CompileShader(GL_VERTEX_SHADER, &vertShader, literal);

		glAttachShader(m_programId, vertShader);
	}

	if (m_geometryShader != NULL)
	{
		std::string literal = LoadTextFile(std::string(m_geometryShader) + GEOM_FILE_EXTENSION);
		CompileShader(GL_GEOMETRY_SHADER, &geometryShader, literal);

		glAttachShader(m_programId, geometryShader);
	}

	if (m_fragShader != NULL)
	{
		std::string literal = LoadTextFile(std::string(m_fragShader) + FRAG_FILE_EXTENSION);
		CompileShader(GL_FRAGMENT_SHADER, &fragShader, literal);

		glAttachShader(m_programId, fragShader);
	}
	
    BindAttribLocations();
	LinkProgram();
	GetUniformIDs();
    
    // Release vertex, hull and fragment shaders.
    if (vertShader) 
	{
        glDetachShader(m_programId, vertShader);
        glDeleteShader(vertShader);
    }
	if (geometryShader)
	{
		glDetachShader(m_programId, geometryShader);
		glDeleteShader(geometryShader);
	}
    if (fragShader) 
	{
		glDetachShader(m_programId, fragShader);
		glDeleteShader(fragShader);
    }
	
	glUseProgram(m_programId);
	PostInitialize();
	
	std::cout << "VCShader Initialized." << std::endl;
	glErrorCheck(); 
}

void VCShader::Bind(VCCamera* camera)
{
	VCShader::BoundCamera = camera;

	if (VCShader::BoundShader == this)
		return;

	VCShader::BoundShader = this;
	glUseProgram(m_programId);
}

void VCShader::CompileShader(GLenum shaderType, GLuint* ShaderId, std::string shaderLiteral)
{
	GLint status;
        
    *ShaderId = glCreateShader(shaderType);
    
	const char *c_str = shaderLiteral.c_str();
	glShaderSource(*ShaderId, 1, &c_str, NULL);
    glCompileShader(*ShaderId);
    
	glGetShaderiv(*ShaderId, GL_COMPILE_STATUS, &status);

//#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*ShaderId, GL_INFO_LOG_LENGTH, &logLength);
	
    if (logLength > 0) 
	{
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*ShaderId, logLength, &logLength, log);

		if (status == 0) 
		{
			SetConsoleColor(Red);

			printf("\n========================  Shader Compilation Error:  ============================\n\n");
			std::istringstream iss(shaderLiteral);
			std::string str;
			int line = 1;
			while(std::getline(iss, str))
				std::cout << std::setw(5) << std::right << line++ << " " << str << std::endl;

			std::cout << std::endl << log << std::endl;;
			free(log);
			VC_ERROR("");
		}
    }

//#endif
    
    if (status == 0) 
	{
        glDeleteShader(*ShaderId);
		VC_ERROR("Failed to compile shader.");
    }

	glErrorCheck();
}

void VCShader::LinkProgram()
{
	GLint status;
    glLinkProgram(m_programId);

    GLint logLength;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &status);

    if (logLength > 0) 
	{
		if (status == 0) 
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetProgramInfoLog(m_programId, logLength, &logLength, log);
			printf("\n========================  Program Link Log:  ==================================\n");
			printf("%s\n\n", log);
			free(log);

			std::cin.ignore();
		}
    }
    
    if (status == 0)
		std::cout << "Failed to link OpenGL program." << std::endl;

	glErrorCheck();
}

bool operator==( const VCShader& lhs, const VCShader& rhs )
{
	return lhs.m_programId == rhs.m_programId;
}

bool operator<( const VCShader& lhs, const VCShader& rhs )
{
	return lhs.m_programId < rhs.m_programId;
}

bool operator!=( const VCShader& lhs, const VCShader& rhs )
{
	return !operator==(lhs,rhs);
}

bool operator>( const VCShader& lhs, const VCShader& rhs )
{
	return  operator< (rhs,lhs);
}

bool operator<=( const VCShader& lhs, const VCShader& rhs )
{
	return !operator> (lhs,rhs);
}

bool operator>=( const VCShader& lhs, const VCShader& rhs )
{
	return !operator< (lhs,rhs);
}
