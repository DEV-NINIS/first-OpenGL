#pragma once
#ifndef DEF_COMPILE_SHADERS
#define DEF_COMPILE_SHADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <string>
#include <sstream>
#include <ostream>
#include <fstream>

class compileShaders
{
public:
	compileShaders(const char* vertexPath, const char* fragmentPath);
	virtual ~compileShaders();
	void load_file();
	void Load_file_shaderPath(const char* vertexPath, const char* fragmentPath);
	void Use_first_program_shader();
	void Use_second_program_shader();
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	GLuint get_shader();
	const char *fragmentShader2_code;
	const char *fragment_shader;
	const char *source;
protected:
	std::string file;
	unsigned int VBO;
	std::string* vertexCodeString;
	std::string* fragmentCodeString;
	char vertexCode;
	char fragmentCode;
	const char* vertexCodeFinal;
	const char* fragmentCodeFinal;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint ShaderProgram;
};


#endif // ! 
