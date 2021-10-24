#include "EyerGLProgram.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLProgram::EyerGLProgram()
    {
        programId = glCreateProgram();
    }

    EyerGLProgram::~EyerGLProgram()
    {
        if(programId != 0) {
            glDeleteProgram(programId);
            programId = 0;
        }
    }

    int EyerGLProgram::AttachShader(EyerGLShader * shader)
    {
        glAttachShader(programId, shader->shaderId);
        return 0;
    }

    int EyerGLProgram::LinkProgram()
    {
        glLinkProgram(programId);
        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            EyerLog("%s\n", &ProgramErrorMessage[0]);
        }

        return 0;
    }

    int EyerGLProgram::UseProgram()
    {
        glUseProgram(programId);
        return 0;
    }

    int EyerGLProgram::PutUniform1i(const EyerString & key, int value)
    {
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1i(location, value);
        return 0;
    }

    int EyerGLProgram::PutUniform1f(const EyerString & key, float value)
    {
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1f(location, value);
        return 0;
    }

    int EyerGLProgram::PutMatrix4fv(const EyerString & key, const EatrixF4x4 & _mat)
    {
        GLuint location = glGetUniformLocation(programId, key.str);

        m4 = _mat.Transpose(m4);
        m4.GetMat(m4data);

        glUniformMatrix4fv(location, 1, GL_FALSE, m4data);

        return 0;
    }

    int EyerGLProgram::PutMatrix3fv(const EyerString & key, const EatrixF3x3 & _mat)
    {
        GLuint location = glGetUniformLocation(programId, key.str);

        EatrixF3x3 mat;
        mat = _mat.Transpose(mat);
        int matLen = mat.GetMatLen();
        float * m = (float *)malloc(matLen);
        mat.GetMat(m);

        glUniformMatrix4fv(location, 1, GL_FALSE, m);

        free(m);

        return 0;
    }
}