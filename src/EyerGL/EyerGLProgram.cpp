#include "EyerGLProgram.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLProgram::EyerGLProgram(OpenGLFunctionsContext * _funcCtx)
    {
        funcCtx = _funcCtx;

#ifdef EYER_PLATFORM_QT
        programId = funcCtx->glCreateProgram();
#else
        programId = glCreateProgram();
#endif
    }

    EyerGLProgram::~EyerGLProgram()
    {
        if(programId != 0) {
#ifdef EYER_PLATFORM_QT
            funcCtx->glDeleteProgram(programId);
#else
            glDeleteProgram(programId);
#endif
            programId = 0;
        }
    }

    int EyerGLProgram::AttachShader(EyerGLShader * shader)
    {
#ifdef EYER_PLATFORM_QT
        funcCtx->glAttachShader(programId, shader->shaderId);
#else
        glAttachShader(programId, shader->shaderId);
#endif
        return 0;
    }

    int EyerGLProgram::LinkProgram()
    {
#ifdef EYER_PLATFORM_QT
        funcCtx->glLinkProgram(programId);
        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        funcCtx->glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        funcCtx->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            funcCtx->glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            EyerLog("%s\n", &ProgramErrorMessage[0]);
        }
#else
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
#endif
        return 0;
    }

    int EyerGLProgram::UseProgram()
    {
#ifdef EYER_PLATFORM_QT
        funcCtx->glUseProgram(programId);
#else
        glUseProgram(programId);
#endif
        
        return 0;
    }

    int EyerGLProgram::PutUniform1i(const EyerString & key, int value)
    {
#ifdef EYER_PLATFORM_QT
        GLuint location = funcCtx->glGetUniformLocation(programId, key.str);
        funcCtx->glUniform1i(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1i(location, value);
#endif
        
        return 0;
    }

    int EyerGLProgram::PutUniform1f(const EyerString & key, float value)
    {
#ifdef EYER_PLATFORM_QT
        GLuint location = funcCtx->glGetUniformLocation(programId, key.str);
        funcCtx->glUniform1f(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1f(location, value);
#endif
        
        return 0;
    }

    int EyerGLProgram::PutMatrix4fv(const EyerString & key, const EatrixF4x4 & _mat)
    {
#ifdef EYER_PLATFORM_QT
        GLuint location = funcCtx->glGetUniformLocation(programId, key.str);

        _mat.GetMat(m4data);

        funcCtx->glUniformMatrix4fv(location, 1, GL_TRUE, m4data);
#else
        GLuint location = glGetUniformLocation(programId, key.str);

        _mat.GetMat(m4data);

        glUniformMatrix4fv(location, 1, GL_TRUE, m4data);
#endif
        

        return 0;
    }

    int EyerGLProgram::PutMatrix3fv(const EyerString & key, const EatrixF3x3 & _mat)
    {
#ifdef EYER_PLATFORM_QT
        GLuint location = glGetUniformLocation(programId, key.str);

        _mat.GetMat(m3data);

        glUniformMatrix3fv(location, 1, GL_TRUE, m3data);
#else
        GLuint location = glGetUniformLocation(programId, key.str);

        _mat.GetMat(m3data);

        glUniformMatrix3fv(location, 1, GL_TRUE, m3data);
#endif
        

        return 0;
    }
}