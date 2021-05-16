#include "POGRenderPCH.h"
#include "Shader.h"

#include "POGDebug.h"
#include "POGLog.h"

#include <glad/glad.h>

namespace POG::Render
{
    Shader::Shader()
        : shader(0)
        , vertexShader(0)
        , fragmentShader(0)
    {
    }

    Shader::~Shader()
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shader);
    }

    void Shader::Init(const char* vertexShaderSource, const char* fragmentShaderSource)
    {
        int success;
        char infoLog[512];

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            POG_ASSERT(success, "Vertex shader failed to compile!");
            POG_ERROR(infoLog);
        }

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            POG_ASSERT(success, "Fragment shader failed to compile!");
            POG_ERROR(infoLog);
        }

        shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            POG_ASSERT(success, "Shader failed to link!");
            POG_ERROR(infoLog);
        }
    }

    void Shader::Use()
    {
        glUseProgram(shader);
    }

    int Shader::GetUniformLocation(const char* uniformName)
    {
        return glGetUniformLocation(shader, uniformName);
    }

    void Shader::Set1f(const char* uniformName, float x)
    {
        glUniform1f(GetUniformLocation(uniformName), x);
    }
    void Shader::Set2f(const char* uniformName, float x, float y)
    {
        glUniform2f(GetUniformLocation(uniformName), x, y);
    }
    void Shader::Set3f(const char* uniformName, float x, float y, float z)
    {
        glUniform3f(GetUniformLocation(uniformName), x, y, z);
    }
    void Shader::Set4f(const char* uniformName, float x, float y, float z, float w)
    {
        glUniform4f(GetUniformLocation(uniformName), x, y, z, w);
    }

    void Shader::Set1i(const char* uniformName, int x)
    {
        glUniform1i(GetUniformLocation(uniformName), x);
    }
    void Shader::Set2i(const char* uniformName, int x, int y)
    {
        glUniform2i(GetUniformLocation(uniformName), x, y);
    }
    void Shader::Set3i(const char* uniformName, int x, int y, int z)
    {
        glUniform3i(GetUniformLocation(uniformName), x, y, z);
    }
    void Shader::Set4i(const char* uniformName, int x, int y, int z, int w)
    {
        glUniform4i(GetUniformLocation(uniformName), x, y, z, w);
    }

    void Shader::Set1ui(const char* uniformName, unsigned int x)
    {
        glUniform1ui(GetUniformLocation(uniformName), x);
    }
    void Shader::Set2ui(const char* uniformName, unsigned int x, unsigned int y)
    {
        glUniform2ui(GetUniformLocation(uniformName), x, y);
    }
    void Shader::Set3ui(const char* uniformName, unsigned int x, unsigned int y, unsigned int z)
    {
        glUniform3ui(GetUniformLocation(uniformName), x, y, z);
    }
    void Shader::Set4ui(const char* uniformName, unsigned int x, unsigned int y, unsigned int z, unsigned int w)
    {
        glUniform4ui(GetUniformLocation(uniformName), x, y, z, w);
    }

    void Shader::Set1fv(const char* uniformName, int count, const float* arr)
    {
        glUniform1fv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set2fv(const char* uniformName, int count, const float* arr)
    {
        glUniform2fv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set3fv(const char* uniformName, int count, const float* arr)
    {
        glUniform3fv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set4fv(const char* uniformName, int count, const float* arr)
    {
        glUniform4fv(GetUniformLocation(uniformName), count, arr);
    }

    void Shader::Set1iv(const char* uniformName, int count, const int* arr)
    {
        glUniform1iv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set2iv(const char* uniformName, int count, const int* arr)
    {
        glUniform2iv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set3iv(const char* uniformName, int count, const int* arr)
    {
        glUniform3iv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set4iv(const char* uniformName, int count, const int* arr)
    {
        glUniform4iv(GetUniformLocation(uniformName), count, arr);
    }

    void Shader::Set1uiv(const char* uniformName, int count, const unsigned int* arr)
    {
        glUniform1uiv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set2uiv(const char* uniformName, int count, const unsigned int* arr)
    {
        glUniform2uiv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set3uiv(const char* uniformName, int count, const unsigned int* arr)
    {
        glUniform3uiv(GetUniformLocation(uniformName), count, arr);
    }
    void Shader::Set4uiv(const char* uniformName, int count, const unsigned int* arr)
    {
        glUniform4uiv(GetUniformLocation(uniformName), count, arr);
    }

    void Shader::SetMatrix2fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix2fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
    void Shader::SetMatrix3fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix3fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
    void Shader::SetMatrix4fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix4fv(GetUniformLocation(uniformName), count, transpose, arr);
    }

    void Shader::SetMatrix2x3fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix2x3fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
    void Shader::SetMatrix3x2fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix3x2fv(GetUniformLocation(uniformName), count, transpose, arr);
    }

    void Shader::SetMatrix2x4fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix2x4fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
    void Shader::SetMatrix4x2fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix4x2fv(GetUniformLocation(uniformName), count, transpose, arr);
    }

    void Shader::SetMatrix3x4fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix3x4fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
    void Shader::SetMatrix4x3fv(const char* uniformName, int count, bool transpose, const float* arr)
    {
        glUniformMatrix4x3fv(GetUniformLocation(uniformName), count, transpose, arr);
    }
}