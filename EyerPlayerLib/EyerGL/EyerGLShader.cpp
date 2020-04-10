#include "EyerGL.hpp"

#include "GLHeader.h"

namespace Eyer{
    EyerGLShader::EyerGLShader(EyerGLShaderType _type, EyerString _src, EyerGLContext * _ctx)
    {
        ctx = _ctx;

        type = _type;
        src = _src;

        GLenum shaderType = GL_VERTEX_SHADER;
        if(type == EyerGLShaderType::VERTEX_SHADER){
            shaderType = GL_VERTEX_SHADER;
        }
        if(type == EyerGLShaderType::FRAGMENT_SHADER){
            shaderType = GL_FRAGMENT_SHADER;
        }

#ifdef QT_EYER_PLAYER
        shaderId = ctx->glCreateShader(shaderType);
#else
        shaderId = glCreateShader(shaderType);
#endif

    }

    EyerGLShader::~EyerGLShader()
    {
        if(shaderId != 0){
#ifdef QT_EYER_PLAYER
            ctx->glDeleteShader(shaderId);
#else
            glDeleteShader(shaderId);
#endif

            shaderId = 0;
        }
    }

    int EyerGLShader::Compile()
    {
        if(shaderId == 0){
            return -1;
        }

#ifdef QT_EYER_PLAYER
        // EyerLog("Shader Src:\n %s\n", src.str);
        ctx->glShaderSource(shaderId, 1, &src.str , NULL);
        ctx->glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;
        ctx->glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        ctx->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            ctx->glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            EyerLog("%s\n", &ShaderErrorMessage[0]);

            EyerLog("Shader Src:\n %s\n", src.str);
        }
#else
        // EyerLog("Shader Src:\n %s\n", src.str);
        glShaderSource(shaderId, 1, &src.str , NULL);
        glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            EyerLog("%s\n", &ShaderErrorMessage[0]);

            EyerLog("Shader Src:\n %s\n", src.str);
        }
#endif

        return 0;
    }

    unsigned int EyerGLShader::GL_GetShaderId()
    {
        return shaderId;
    }
}
