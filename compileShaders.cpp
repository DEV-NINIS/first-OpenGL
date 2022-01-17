#include "compileShaders.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template <class T>
inline const char* xToString(const T& t) {
    std::basic_ostringstream<char> o;
    o << t;
    return o.str().c_str();
}
compileShaders::compileShaders(const char* vertexPath, const char* fragmentPath) { file; VBO;
vertexShader;
fragmentShader;
ShaderProgram;
vertexCode; vertexCodeString = new std::string;
fragmentCode; fragmentCodeString = new std::string;
vertexCodeFinal; fragmentCodeFinal;
source = "#version 460 core\n"

"layout (location = 0) in vec3 aPos;\n" // la variable position a l'attribut de position 0
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"

"uniform float position;\n"
"uniform mat4 transform;\n"
"out vec3 ourColor;\n" // nous definirons la couleur dans cette variable 
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
    "   gl_Position = transform * vec4(aPos, 1.0f);\n"
    "   ourColor = aColor;\n"
    "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\n\0";

fragment_shader = "#version 460 core\n"

"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"

"void main()\n"
"{\n"
"   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5) * vec4(ourColor, 1.0);\n"
"}\n\0";
fragmentShader2_code = "#version 460 core\n"

"out vec4 FragColor;\n"
"in vec3 ourColor;\n"

"void main()\n"
"{\n"
"   FragColor = ;\n"
"}\n\0";
}
compileShaders::~compileShaders() {
    // delete of shaders
    glDeleteProgram(ShaderProgram);
    //
}

void compileShaders::load_file() {
    int nbatt;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nbatt);
    cout << nbatt << endl;
    //
    // compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**)&source, NULL);
    glCompileShader(vertexShader);
    //
         // variables of get _success_compile
    int success_compile_shader;
    int success_compile_fragment_shader;
        //
    // compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragment_shader, NULL);
    glCompileShader(fragmentShader);
    //
        // verification of compilation shaders
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_compile_shader);
    if (!success_compile_shader) {
        cout << " erreur lors de la compillation des shaders " << infolog << endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_compile_fragment_shader);
    if (!success_compile_fragment_shader) {
        cout << " erreur lors de la compillation du fragment shader " << endl;
    }
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_compile_shader);
    if (!success_compile_shader) {
        cout << " erreur lors de la compillation du vertex shader " << infolog << endl;
    }
        //
    // program shader 
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);
    //
    // 
}
void compileShaders::Load_file_shaderPath(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode2;
    std::string fragmentCode2;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // s'assure que les objets ifstream peuvent envoyer des exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ouverture des fichiers
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // lecture des fichiers et place le contenu dans des flux
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // fermeture des fichiers
        vShaderFile.close();
        fShaderFile.close();
        // convertions des flux en string
        vertexCode2 = vShaderStream.str();
        fragmentCode2 = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode2.c_str();
    const char* fShaderCode = fragmentCode2.c_str();
    vertexCodeFinal = vShaderCode;
    fragmentCodeFinal = fShaderCode;
}

void compileShaders::Use_first_program_shader() {
    glUseProgram(ShaderProgram);
}
void compileShaders::Use_second_program_shader() {
    glUseProgram(ShaderProgram);
}
GLuint compileShaders::get_shader() {
    return ShaderProgram;
}
void compileShaders::setBool(const std::string& name, bool value) const 
{
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value);
}
void compileShaders::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}
void compileShaders::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}
void compileShaders::use() {
    glUseProgram(ShaderProgram);
}