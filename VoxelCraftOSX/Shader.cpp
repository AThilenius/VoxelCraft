#include "Shader.h"


Shader::Shader()
{
	m_programId = -1;
	m_vertexShaderLiteral = NULL;
	m_fragShaderLiteral = NULL;
	m_geometryShaderLiteral = NULL;
}

Shader::~Shader()
{
	if ( m_programId != -1 )
	{
		glDeleteProgram(m_programId);
		m_programId = -1;
	}
}

void Shader::Initialize()
{
	GLuint vertShader, geometryShader, fragShader = 0;
	
    // Create shader program.
	m_programId = glCreateProgram();
    
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

	glErrorCheck();
        
}

void Shader::Bind()
{
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
			CONSOLE_COLOR_RED;
		}
		else
		{
			CONSOLE_COLOR_GREEN;
		}

		printf("\n========================  Shader compellation log:  ===========================\n");
        printf("%s\n\n", log);
        free(log);

		CONSOLE_COLOR_WHITE;
    }
//#endif
    
    if (status == 0) 
	{
        glDeleteShader(*ShaderId);
        cout << "Failed to compile shader." << endl;
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
			CONSOLE_COLOR_RED;
		}
		else
		{
			CONSOLE_COLOR_GREEN;
		}


        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(m_programId, logLength, &logLength, log);
		printf("\n========================  Program Link Log:  ==================================\n");
        printf("%s\n\n", log);
        free(log);

		CONSOLE_COLOR_WHITE;
    }
    
    if (status == 0)
		cout << "Failed to link OpenGL program." << endl;

	glErrorCheck();
}