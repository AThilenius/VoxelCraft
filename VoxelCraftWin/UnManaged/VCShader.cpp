//
//  Shader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCShader.h"
#include "VCObjectStore.h"
#include "json/json.h"
#include "VCPathUtilities.h"
#include "VCResourceManager.h"

VCShader* VCShader::BoundShader = NULL;
std::unordered_map<std::string, VCShader*> VCShader::LoadedShaders;


VCShader::VCShader():
	m_programId(0)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);

	// Auto add MVP
	Uniforms.push_back(VCShaderUniform(VCShaderUniform::Matrix4, std::string("MVP")));
}

VCShader::~VCShader()
{
	if ( m_programId != 0 )
	{
		/*glDeleteProgram(m_programId);
		m_programId = 0;*/

		LoadedShaders.erase(Name);
	}
}

VCShader* VCShader::GetShader( std::string name )
{
	auto iter = LoadedShaders.find(name);

	if (iter != LoadedShaders.end())
		return iter->second;

	// Load a new shader
	std::string path = VCPathUtilities::Combine(VCPathUtilities::VCShadersPath, name + ".vcshader");
	std::string shaderJson = LoadTextFile(path);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( shaderJson, root );

	if ( !parsingSuccessful )
	{
		VC_ERROR("Failed to parse shader JSON file: " << path);
	}

	VCShader* shader = new VCShader();

	// Name
	shader->Name = root.get("Name", "").asString();

	// Attributes
	{
		const Json::Value attribs = root["Attributes"];

		for ( int i = 0; i < attribs.size(); i++ )
		{
			std::string attributeType = attribs[i].get("AttributeType", "").asString();
			std::string attribName = attribs[i].get("Name", "").asString();
			shader->Attributes.push_back(VCShaderAttribute(VCShaderAttribute::GetID(attributeType), attribName));
		}
	}

	// Uniforms
	{
		const Json::Value uniforms = root["Uniforms"];

		for ( int i = 0; i < uniforms.size(); i++ )
		{
			std::string valueType = uniforms[i].get("ValueType", "").asString();
			std::string valueName = uniforms[i].get("Name", "").asString();
			shader->Uniforms.push_back(VCShaderUniform(VCShaderUniform::GetID(valueType), valueName));
		}
	}

	shader->VertexShader = root.get("VertexShader", "").asString();
	shader->GeometryShader = root.get("GeometryShader", "").asString();
	shader->FragmentShader = root.get("FragmentShader", "").asString();

	shader->Compile();

	return shader;
}

void VCShader::Compile()
{
	GLuint vertShader = 0;
	GLuint geometryShader = 0;
	GLuint fragShader = 0;
	
    // Create shader program.
	GLuint id = glCreateProgram();
	
	m_programId = id;
    
	// =====   Create and compile shaders   ======================================================
	if (VertexShader != "")
	{
		CompileShader(GL_VERTEX_SHADER, &vertShader, VertexShader);

		if (vertShader) 
			glAttachShader(m_programId, vertShader);
	}

	if (GeometryShader != "")
	{
		CompileShader(GL_GEOMETRY_SHADER, &geometryShader, GeometryShader);

		if (geometryShader)
			glAttachShader(m_programId, geometryShader);
	}

	if (FragmentShader != "")
	{
		CompileShader(GL_FRAGMENT_SHADER, &fragShader, FragmentShader);

		if (fragShader) 
			glAttachShader(m_programId, fragShader);
	}
	
    BindAttribLocations();
	PreLink();
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
	LoadedShaders.insert(std::unordered_map<std::string, VCShader*>::value_type(Name, this));

	std::cout << "VCShader [ " << Name << " ] Initialized." << std::endl;
	glErrorCheck(); 
}

void VCShader::Bind()
{
	if (VCShader::BoundShader == this)
		return;

	VCShader::BoundShader = this;
	glUseProgram(m_programId);
}

void VCShader::SetMVP( glm::mat4 mvp )
{
	SetUniform(0, mvp);
}

void VCShader::SetUniform(int index, int value)
{
	glUniform1i(Uniforms[index].OpenGlID, value);
}

void VCShader::SetUniform(int index, float value)
{
	glUniform1f(Uniforms[index].OpenGlID, value);
}

void VCShader::SetUniform(int index, glm::vec2 value)
{
	glUniform2fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCShader::SetUniform(int index, glm::vec3 value)
{
	glUniform3fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCShader::SetUniform(int index, glm::vec4 value)
{
	glUniform4fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCShader::SetUniform(int index, glm::mat3 value)
{
	glUniformMatrix3fv(Uniforms[index].OpenGlID, 1, GL_FALSE, &value[0][0]);
}

void VCShader::SetUniform(int index, glm::mat4 value)
{
	glUniformMatrix4fv(Uniforms[index].OpenGlID, 1, GL_FALSE, &value[0][0]);
}

int VCShader::GetUniformIndex( std::string name )
{
	for (int i = 0; i < Uniforms.size(); i++)
		if (Uniforms[i].Name == name)
			return i;

	return -1;
}

GLuint VCShader::GetUniformID( std::string name )
{
	for (int i = 0; i < Uniforms.size(); i++)
		if (Uniforms[i].Name == name)
			return Uniforms[i].OpenGlID;

	return 0;
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

void VCShader::BindAttribLocations()
{
	for (int i = 0; i < Attributes.size(); i++)
	{
		VCShaderAttribute attrib = Attributes[i];
		glBindAttribLocation(m_programId, attrib.ID, attrib.Name.c_str());
	}
}

void VCShader::GetUniformIDs()
{
	for (int i = 0; i < Uniforms.size(); i++)
	{
		VCShaderUniform uniform = Uniforms[i];
		Uniforms[i].OpenGlID = glGetUniformLocation(m_programId, uniform.Name.c_str());
	}
}

void VCShader::PreLink()
{
	// Transform Feedback stuff here
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

int VCInteropGetShaderFromFile( char* name )
{
	return VCResourceManager::GetShader(std::string(name))->Handle;
}

void VCInteropShaderSetUniformInt(int handle, int index, int value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformFloat(int handle, int index, float value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec2(int handle, int index, glm::vec2 value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec3(int handle, int index, glm::vec3 value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec4(int handle, int index, glm::vec4 value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformMat3(int handle, int index, glm::mat3 value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformMat4(int handle, int index, glm::mat4 value)
{
	VCShader* shader = (VCShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}
