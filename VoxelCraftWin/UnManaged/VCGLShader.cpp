//
//  Shader.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLShader.h"
#include "VCObjectStore.h"
#include "json/json.h"
#include "VCPathUtilities.h"
#include "VCResourceManager.h"
#include "VCCamera.h"

VCGLShader* VCGLShader::BoundShader = NULL;
std::unordered_map<std::string, VCGLShader*> VCGLShader::LoadedShaders;


VCGLShader::VCGLShader():
	m_programId(0),
	m_boundCamera(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);

	// Auto add MVP
	//Uniforms.push_back(VCShaderUniform(VCShaderUniform::Matrix4, std::string("MVP")));
}

VCGLShader::~VCGLShader()
{
	if ( m_programId != 0 )
	{
		/*glDeleteProgram(m_programId);
		m_programId = 0;*/

		LoadedShaders.erase(Name);
	}
}

VCGLShader* VCGLShader::GetShader( std::string path, bool forceReload )
{
	VCGLShader* shader = NULL;
	auto iter = LoadedShaders.find(path);

	if (iter != LoadedShaders.end())
	{
		// Existing shader, do we need to reload it?
		if ( !forceReload )
			return iter->second;

		else
		{
			// reload shader
			shader = iter->second;
			shader->FreeGLShader();
		}
	}

	else
	{
		// New Shader
		shader = new VCGLShader();
	}

	// Load a new shader
	std::string shaderJson = LoadTextFile(path);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( shaderJson, root );

	if ( !parsingSuccessful )
		VCLog::Error("Failed to parse shader JSON file: " + path, "Shader");

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

	// Perpend Vertex Uniforms
	shader->VertexShader = PerpendLine("uniform mat4 VC_MvpMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform mat4 VC_ModelMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform mat4 VC_ViewMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform mat4 VC_ProjectionMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform mat4 VC_ModelViewMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform mat4 VC_ViewProjectionMatrix;", shader->VertexShader);
	shader->VertexShader = PerpendLine("uniform vec3 VC_LightInverseDirection;", shader->VertexShader);

	// Perpend GLSL version to each
	if (shader->GeometryShader != "")
		shader->GeometryShader = PerpendLine("#version " + std::to_string(VC_GLSL_VERSION), shader->GeometryShader);
	shader->VertexShader = PerpendLine("#version " + std::to_string(VC_GLSL_VERSION), shader->VertexShader);
	shader->FragmentShader = PerpendLine("#version " + std::to_string(VC_GLSL_VERSION), shader->FragmentShader);

	shader->Compile();


	if (iter == LoadedShaders.end())
	{
		LoadedShaders.insert(std::unordered_map<std::string, VCGLShader*>::value_type(path, shader));
		VCLog::Info("VCGLShader [ " + shader->Name + " ] Initialized.", "Resources");
	}

	else
		VCLog::Info("VCGLShader [ " + shader->Name + " ] Re-Initialized.", "Resources");

	return shader;
}

void VCGLShader::Compile()
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
	glErrorCheck();
}

void VCGLShader::Bind()
{
	// Bind The Shader
	if (VCGLShader::BoundShader != this)
	{
		VCGLShader::BoundShader = this;
		glUseProgram(m_programId);
	}
}

void VCGLShader::SetCamera( VCCamera* camera )
{
	if (camera != m_boundCamera || camera->WasUpdated)
	{
		m_boundCamera = camera;
		m_viewMatrix = camera->ViewMatrix;
		m_projectionMatrix = camera->ProjectionMatrix;
		m_lightInverseDirection = camera->LightInverseDirection;

		if (m_unifViewMatrix != VC_UNIFORM_DNE)
			glUniformMatrix4fv(m_unifViewMatrix, 1, GL_FALSE, &camera->ViewMatrix[0][0]);

		if (m_unifProjectionMatrix != VC_UNIFORM_DNE)
			glUniformMatrix4fv(m_unifProjectionMatrix, 1, GL_FALSE, &camera->ProjectionMatrix[0][0]);

		if (m_unifViewProjectionMatrix != VC_UNIFORM_DNE)
			glUniformMatrix4fv(m_unifProjectionMatrix, 1, GL_FALSE, &camera->ProjectionViewMatrix[0][0]);

		if (m_unifLightInverseDirection != VC_UNIFORM_DNE)
			glUniform3fv(m_unifLightInverseDirection, 1, &camera->LightInverseDirection[0]);
	}
}

void VCGLShader::SetModelMatrix( glm::mat4 modelMatrix )
{
	if (m_unifModelMatrix != VC_UNIFORM_DNE)
	{
		glUniformMatrix4fv(m_unifModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
		m_modelMatrix = modelMatrix;
	}

	if (m_unifMvpMatrix != VC_UNIFORM_DNE)
	{
		glm::mat4 mvp = m_projectionMatrix * m_viewMatrix * modelMatrix;
		glUniformMatrix4fv(m_unifMvpMatrix, 1, GL_FALSE, &mvp[0][0]);
	}
	
	if (m_unifModelViewMatrix != VC_UNIFORM_DNE)
	{
		glm::mat4 mv = m_viewMatrix * modelMatrix;
		glUniformMatrix4fv(m_unifMvpMatrix, 1, GL_FALSE, &mv[0][0]);
	}
}

void VCGLShader::SetUniform(int index, int value)
{
	glUniform1i(Uniforms[index].OpenGlID, value);
}

void VCGLShader::SetUniform(int index, float value)
{
	glUniform1f(Uniforms[index].OpenGlID, value);
}

void VCGLShader::SetUniform(int index, glm::vec2 value)
{
	glUniform2fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCGLShader::SetUniform(int index, glm::vec3 value)
{
	glUniform3fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCGLShader::SetUniform(int index, glm::vec4 value)
{
	glUniform4fv(Uniforms[index].OpenGlID, 1, &value[0]);
}

void VCGLShader::SetUniform(int index, glm::mat3 value)
{
	glUniformMatrix3fv(Uniforms[index].OpenGlID, 1, GL_FALSE, &value[0][0]);
}

void VCGLShader::SetUniform(int index, glm::mat4 value)
{
	glUniformMatrix4fv(Uniforms[index].OpenGlID, 1, GL_FALSE, &value[0][0]);
}

int VCGLShader::GetUniformIndex( std::string name )
{
	for (int i = 0; i < Uniforms.size(); i++)
		if (Uniforms[i].Name == name)
			return i;

	return -1;
}

GLuint VCGLShader::GetUniformID( std::string name )
{
	for (int i = 0; i < Uniforms.size(); i++)
		if (Uniforms[i].Name == name)
			return Uniforms[i].OpenGlID;

	return 0;
}

void VCGLShader::CompileShader(GLenum shaderType, GLuint* ShaderId, std::string shaderLiteral)
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

void VCGLShader::LinkProgram()
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
		VCLog::Error("Failed to link OpenGL program.", "Resources");

	glErrorCheck();
}

void VCGLShader::BindAttribLocations()
{
	for (int i = 0; i < Attributes.size(); i++)
	{
		VCShaderAttribute attrib = Attributes[i];
		glBindAttribLocation(m_programId, attrib.ID, attrib.Name.c_str());
	}
}

void VCGLShader::GetUniformIDs()
{
	// Get VC_* Uniforms
	m_unifMvpMatrix = glGetUniformLocation(m_programId, "VC_MvpMatrix");
	m_unifModelMatrix = glGetUniformLocation(m_programId, "VC_ModelMatrix");
	m_unifViewMatrix = glGetUniformLocation(m_programId, "VC_ViewMatrix");
	m_unifProjectionMatrix = glGetUniformLocation(m_programId, "VC_ProjectionMatrix");
	m_unifModelViewMatrix = glGetUniformLocation(m_programId, "VC_ModelViewMatrix");
	m_unifViewProjectionMatrix = glGetUniformLocation(m_programId, "VC_ViewProjectionMatrix");
	m_unifLightInverseDirection = glGetUniformLocation(m_programId, "VC_LightInverseDirection");
	
	// Add JSON Uniforms
	for (int i = 0; i < Uniforms.size(); i++)
	{
		VCShaderUniform uniform = Uniforms[i];
		Uniforms[i].OpenGlID = glGetUniformLocation(m_programId, uniform.Name.c_str());
	}
}

void VCGLShader::PreLink()
{
	// Transform Feedback stuff here
}

void VCGLShader::FreeGLShader()
{
	if (m_programId != 0)
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}

bool operator==( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return lhs.m_programId == rhs.m_programId;
}

bool operator<( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return lhs.m_programId < rhs.m_programId;
}

bool operator!=( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return !operator==(lhs,rhs);
}

bool operator>( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return  operator< (rhs,lhs);
}

bool operator<=( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return !operator> (lhs,rhs);
}

bool operator>=( const VCGLShader& lhs, const VCGLShader& rhs )
{
	return !operator< (lhs,rhs);
}

int VCInteropGetShaderFromFile( char* fullPath )
{
	return VCResourceManager::GetShader(std::string(fullPath))->Handle;
}

void VCInteropReloadShader( char* fullPath )
{
	VCResourceManager::ReloadShader(fullPath);
}

void VCInteropShaderSetUniformInt(int handle, int index, int value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformFloat(int handle, int index, float value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec2(int handle, int index, glm::vec2 value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec3(int handle, int index, glm::vec3 value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformVec4(int handle, int index, glm::vec4 value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformMat3(int handle, int index, glm::mat3 value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}

void VCInteropShaderSetUniformMat4(int handle, int index, glm::mat4 value)
{
	VCGLShader* shader = (VCGLShader*) VCObjectStore::Instance->GetObject(handle);
	shader->SetUniform(index, value);
}