#pragma once
#include <string>

struct ShaderProgramSource
{
	std::string vertex_source;
	std::string fragment_source;
};


class Shader
{
public:
	Shader() = delete;
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	static unsigned int create_program_from_shader_files(const char* vertex_path, const char* fragment_path);
	static unsigned int create_program(const char* vertex_shader, const char* fragment_shader);
	static int create_and_compile_shader(const char* source, unsigned int type);
private:
	static std::string read_file(const char* file_path);
};

