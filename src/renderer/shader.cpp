#include "shader.h"

Shader::Shader(const char *vPath, const char *fPath)
{

    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode = Loader::loadFile(vPath);
    std::string fragmentCode = Loader::loadFile(fPath);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const *vertexSourcePointer = vertexCode.c_str();
    glShaderSource(vertexID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(vertexID, InfoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    char const *fragmentSourcePointer = fragmentCode.c_str();
    glShaderSource(fragmentID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(fragmentID, InfoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        printf("%s\n", &fragmentShaderErrorMessage[0]);
    }

    id = glCreateProgram();

    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &Result);
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(id, vertexID);
    glDetachShader(id, fragmentID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

Shader::~Shader()
{

}

void Shader::bind()
{
    glUseProgram(id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::setUniform(const char *name, maths::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, (GLchar*) name), 1, GL_FALSE, &matrix.m_matrix[0]);
}

void Shader::setUniform(const char *name, float a)
{
    glUniform1f(glGetUniformLocation(id, (GLchar*) name), a);
}

void Shader::setUniform(const char *name, int a)
{
    glUniform1i(glGetUniformLocation(id, (GLchar*) name), a);
}

void Shader::setUniform(const char *name, maths::vec3 a)
{
    glUniform3f(glGetUniformLocation(id, (GLchar*) name), a.x, a.y, a.z);
}
