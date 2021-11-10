#include "EyerGLShader.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLShader::EyerGLShader(EyerGLShaderType _type, const EyerString & _src, OpenGLFunctionsContext * _funcCtx)
    {
        funcCtx = _funcCtx;

        type = _type;
        src = _src;

#ifdef EYER_PLATFORM_ANDROID

#elif EYER_PLATFORM_IOS

#else
        // src.ReplaceAll("#version 300 es", "#version 330");
#endif

        GLenum shaderType = GL_VERTEX_SHADER;
        if(type == EyerGLShaderType::VERTEX_SHADER){
            shaderType = GL_VERTEX_SHADER;
        }
        if(type == EyerGLShaderType::FRAGMENT_SHADER){
            shaderType = GL_FRAGMENT_SHADER;
        }
#ifdef EYER_PLATFORM_QT
#else
#endif

#ifdef EYER_PLATFORM_QT
        shaderId = funcCtx->glCreateShader(shaderType);
#else
        shaderId = glCreateShader(shaderType);
#endif
    }

    EyerGLShader::~EyerGLShader()
    {
        if(shaderId != 0){
#ifdef EYER_PLATFORM_QT
            funcCtx->glDeleteShader(shaderId);
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

#ifdef EYER_PLATFORM_QT
        funcCtx->glShaderSource(shaderId, 1, &src.str , NULL);
        funcCtx->glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        funcCtx->glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        funcCtx->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            funcCtx->glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            EyerLog("Shader Src:\n %s\n", src.str);
            EyerLog("%s\n", &ShaderErrorMessage[0]);
        }
        
#else
        glShaderSource(shaderId, 1, &src.str , NULL);
        glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            EyerLog("Shader Src:\n %s\n", src.str);
            EyerLog("%s\n", &ShaderErrorMessage[0]);
        }
#endif
        

        return 0;
    }
}