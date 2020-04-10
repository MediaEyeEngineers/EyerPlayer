#include "EyerGL.hpp"

#include "GLHeader.h"
#include <stdio.h>
#include <stdlib.h>

namespace Eyer
{
    EyerGLProgram::EyerGLProgram(EyerString _vertexShaderSrc, EyerString _fragmentShaderSrc, EyerGLContext * _ctx)
    {
        ctx = _ctx;
        vertexShaderSrc = _vertexShaderSrc;
        fragmentShaderSrc = _fragmentShaderSrc;
#ifdef QT_EYER_PLAYER
        programId = ctx->glCreateProgram();
#else
        programId = glCreateProgram();
#endif
    }

    EyerGLProgram::~EyerGLProgram()
    {
        if(programId != 0) {
#ifdef QT_EYER_PLAYER
            ctx->glDeleteProgram(programId);
#else
            glDeleteProgram(programId);
#endif
            programId = 0;
        }
    }

    int EyerGLProgram::LinkProgram()
    {
        Eyer::EyerGLShader vertexShader(Eyer::EyerGLShaderType::VERTEX_SHADER, vertexShaderSrc, ctx);
        vertexShader.Compile();

        Eyer::EyerGLShader fragmentShader(Eyer::EyerGLShaderType::FRAGMENT_SHADER, fragmentShaderSrc, ctx);
        fragmentShader.Compile();

#ifdef QT_EYER_PLAYER
        ctx->glAttachShader(programId, vertexShader.GL_GetShaderId());
        ctx->glAttachShader(programId, fragmentShader.GL_GetShaderId());

        ctx->glLinkProgram(programId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        ctx->glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        ctx->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            ctx->glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            EyerLog("%s\n", &ProgramErrorMessage[0]);

            EyerLog("%s\n", vertexShaderSrc.str);
            EyerLog("%s\n", fragmentShaderSrc.str);
        }
#else
        glAttachShader(programId, vertexShader.GL_GetShaderId());
        glAttachShader(programId, fragmentShader.GL_GetShaderId());

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

            EyerLog("%s\n", vertexShaderSrc.str);
            EyerLog("%s\n", fragmentShaderSrc.str);
        }
#endif


        return 0;
    }

    int EyerGLProgram::UseProgram()
    {
#ifdef QT_EYER_PLAYER
        ctx->glUseProgram(programId);
#else
        glUseProgram(programId);
#endif

        return 0;
    }

    int EyerGLProgram::PutUniform1i(EyerString key, int value)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
        ctx->glUniform1i(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1i(location, value);
#endif


        return 0;
    }

    int EyerGLProgram::PutUniform1f(EyerString key, float value)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
        ctx->glUniform1f(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1f(location, value);
#endif

        return 0;
    }

    int EyerGLProgram::PutMatrix4fv(EyerString key, EyerMat4x4 & _mat)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
#endif


        EyerMat4x4 mat = ~_mat;
        int matLen = mat.GetMatLen();
        float * m = (float *)malloc(matLen);
        mat.GetMat(m);

#ifdef QT_EYER_PLAYER
        ctx->glUniformMatrix4fv(location, 1, GL_FALSE, m);
#else
        glUniformMatrix4fv(location, 1, GL_FALSE, m);
#endif

        free(m);

        return 0;
    }
}
