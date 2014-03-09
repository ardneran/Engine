//
//  GlShader.cpp
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "GlShader.h"

namespace Engine
{
	std::vector<GLuint> GlShader::loadShaders(const std::map<std::string, GLenum>& shaderFileTypePairs)
	{
		std::vector<GLuint> shaders;
		
		for (std::map<std::string, GLuint>::const_iterator shaderPair = shaderFileTypePairs.begin(); shaderPair != shaderFileTypePairs.end(); ++shaderPair)
		{
			std::string strFilename = Utils::singleton()->findFile(shaderPair->first);
			if (strFilename != "")
			{
				std::ifstream shaderFile(strFilename.c_str());
				std::stringstream shaderData;
				shaderData << shaderFile.rdbuf();
				shaderFile.close();
				
				const char *shaderString = shaderData.str().c_str();
				
				GLuint shader = glCreateShader(shaderPair->second);
				glShaderSource(shader, 1, &shaderString, NULL);
				glCompileShader(shader);
				
				GLint status;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
				if (status == GL_FALSE)
				{
					GLint logLength;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
					GLchar *logString = new GLchar[logLength + 1];
					glGetProgramInfoLog(shader, logLength, NULL, logString);
					
					fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderPair->first.c_str(), logString);
					delete [] logString;
				}
				shaders.push_back(shader);
			}
		}
		return shaders;
	}
		
	GLuint GlShader::createProgram(const std::vector<GLuint>& shaders)
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint>::const_iterator shader;
		
		for (shader = shaders.begin(); shader != shaders.end(); ++shader)
		{
			glAttachShader(program, *shader);
		}
				
		glLinkProgram(program);
		
		GLint status;

		glGetProgramiv(program, GL_LINK_STATUS, &status);
		
		if (status == GL_FALSE)
		{
			GLint logLenth;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLenth);
			GLchar *logString = new GLchar[logLenth + 1];
			glGetProgramInfoLog(program, logLenth, NULL, logString);
			fprintf(stderr, "Linker failure: %s\n", logString);
			delete [] logString;
		}
		
		for (shader = shaders.begin(); shader != shaders.end(); ++shader)
		{
			glDetachShader(program, *shader);
			glDeleteShader(*shader);
		}

		return program;
	}
	
}
