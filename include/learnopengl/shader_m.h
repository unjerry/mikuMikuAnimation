#ifndef SHADER_M_H
#define SHADER_M_H

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    GladGLContext *gl;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char *vertexPath, const char *fragmentPath)
    {
        gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        int version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = gl->CreateShader(GL_VERTEX_SHADER);
        gl->ShaderSource(vertex, 1, &vShaderCode, NULL);
        gl->CompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = gl->CreateShader(GL_FRAGMENT_SHADER);
        gl->ShaderSource(fragment, 1, &fShaderCode, NULL);
        gl->CompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = gl->CreateProgram();
        gl->AttachShader(ID, vertex);
        gl->AttachShader(ID, fragment);
        gl->LinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        gl->DeleteShader(vertex);
        gl->DeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use() const
    {
        gl->UseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        gl->Uniform1i(gl->GetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        gl->Uniform1i(gl->GetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        gl->Uniform1f(gl->GetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        gl->Uniform2fv(gl->GetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        gl->Uniform2f(gl->GetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        gl->Uniform3fv(gl->GetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        gl->Uniform3f(gl->GetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        gl->Uniform4fv(gl->GetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        gl->Uniform4f(gl->GetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        gl->UniformMatrix2fv(gl->GetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        gl->UniformMatrix3fv(gl->GetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        gl->UniformMatrix4fv(gl->GetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            gl->GetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                gl->GetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            gl->GetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                gl->GetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif