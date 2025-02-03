#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

std::string Shader::read_file(const char* file_path)
{
	std::ifstream file(file_path);
	if (!file.is_open()) {
		std::cout << "Failed to open shader file: " << file_path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

unsigned int Shader::create_program_from_shader_files(const char* vertex_path, const char* fragment_path)
{
	std::string vertex_source = read_file(vertex_path);
	if (vertex_source.empty()) {
		std::cout << "Failed to read vertex shader from: " << vertex_path << std::endl;
		return 0;
	}

	std::string fragment_source = read_file(fragment_path);
	if (fragment_source.empty()) {
		std::cout << "Failed to read fragment shader from: " << fragment_path << std::endl;
		return 0;
	}

	return create_program(vertex_source.c_str(), fragment_source.c_str());
}

unsigned int Shader::create_program(const char* vertex_shader, const char* fragment_shader)
{
	unsigned int vertex = create_and_compile_shader(vertex_shader, GL_VERTEX_SHADER);
	if (vertex == static_cast<unsigned int>(-1)) {
		return 0;
	}

	unsigned int fragment = create_and_compile_shader(fragment_shader, GL_FRAGMENT_SHADER);
	if (fragment == static_cast<unsigned int>(-1)) {
		glDeleteShader(vertex);
		return 0;
	}

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint success;
	char info_log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
		std::cout << "Program linking failed: " << info_log << std::endl;
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return 0;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	glUseProgram(program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return program;
}

int Shader::create_and_compile_shader(const char* source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint success;
	char info_log[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, sizeof(info_log), nullptr, info_log);
		std::cout << "Shader compilation failed: " << info_log << std::endl;
		glDeleteShader(id);
		return -1;
	}

	return id;
}
