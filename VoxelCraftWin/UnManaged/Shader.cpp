//
//  Shader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "Shader.h"

Shader* Shader::BoundShader;

Shader::Shader()
{
	m_programId = 0;
	m_vertexShaderLiteral = NULL;
	m_fragShaderLiteral = NULL;
	m_geometryShaderLiteral = NULL;
}

Shader::~Shader()
{
	if ( m_programId != 0 )
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}

void Shader::Initialize()
{
	
	GLuint vertShader, geometryShader, fragShader = 0;
	
    // Create shader program.
	GLuint id = glCreateProgram();
	
	m_programId = id;
    
    // Create and compile vertex shader.
    CompileShader(GL_VERTEX_SHADER, &vertShader, m_vertexShaderLiteral);
	CompileShader(GL_FRAGMENT_SHADER, &fragShader, m_fragShaderLiteral);
	
	if ( m_geometryShaderLiteral != NULL )
		CompileShader(GL_GEOMETRY_SHADER, &geometryShader, m_geometryShaderLiteral);
	
    // Attach vertex shader to program.
    glAttachShader(m_programId, vertShader);
    glAttachShader(m_programId, fragShader);
	
	if ( m_geometryShaderLiteral != NULL )
		glAttachShader(m_programId, geometryShader);
    
	
    BindAttribLocations();
	LinkProgram();
	GetUniformIDs();
    
    // Release vertex, hull and fragment shaders.
    if (vertShader) 
	{
        glDetachShader(m_programId, vertShader);
        glDeleteShader(vertShader);
    }
	if ( m_geometryShaderLiteral != NULL && geometryShader )
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
	
	cout << "VCShader Initialized." << endl;
	glErrorCheck(); 
}

void Shader::Bind()
{
	Shader::BoundShader = this;
	glUseProgram(m_programId);
}

void Shader::CompileShader(GLenum shaderType, GLuint* ShaderId, string* shaderLiteral)
{
	GLint status;
        
    *ShaderId = glCreateShader(shaderType);
    
	const char *c_str = shaderLiteral->c_str();
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
			printf("\n========================  Shader compellation log:  ===========================\n");
			printf("%s\n\n", log);
			free(log);
		}
    }

//#endif
    
    if (status == 0) 
	{
        glDeleteShader(*ShaderId);
        cout << "Failed to compile shader." << endl;
		cin.ignore();
    }

	glErrorCheck();
}

void Shader::LinkProgram()
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

			cin.ignore();
		}
    }
    
    if (status == 0)
		cout << "Failed to link OpenGL program." << endl;

	glErrorCheck();
}