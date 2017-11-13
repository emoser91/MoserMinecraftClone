#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER); //Vertex shader
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER); // Fragment shader

	//Add all shaders to the shader program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//Tells opengl what part of data to read in as what variable in the shader program
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	//Link program for shaders
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	//Validate program for shaders
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[TRANSFROM_U] = glGetUniformLocation(m_program, "transform");
	//m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	//m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

Shader::~Shader()
{
	//Delete all individual shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

//Method that overrides any shader functions and runs this one
void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
//void Shader::Update(const Transform& transform)
{
	//glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFROM_U], 1, GL_FALSE, &model[0][0]);
}

//Method that loads a text file from the hard drive
std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

//Method that checks for any shader errors
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	//cheak to make sure that shader creation worked
	if (shader == 0)
	{
		std::cerr << "Error compiling shader type " << type << std::endl;
	}

	//Convert imported string to a list of one c.string
	const GLchar* shaderSourceStrings[1];
	shaderSourceStrings[0] = text.c_str();
	GLint lengths[1]; //length of shader source strings
	lengths[0] = text.length();

	//Send shader code to be processed by the GPU and check for error
	glShaderSource(shader, 1, shaderSourceStrings, lengths);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}