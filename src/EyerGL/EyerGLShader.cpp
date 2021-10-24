#include "EyerGLShader.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLShader::EyerGLShader(EyerGLShaderType _type, const EyerString & _src)
    {
        type = _type;
        src = _src;

#ifdef EYER_PLATFORM_ANDROID

#elif EYER_PLATFORM_IOS

#else
        src.ReplaceAll("#version 300 es", "#version 330");
#endif

        GLenum shaderType = GL_VERTEX_SHADER;
        if(type == EyerGLShaderType::VERTEX_SHADER){
            shaderType = GL_VERTEX_SHADER;
        }
        if(type == EyerGLShaderType::FRAGMENT_SHADER){
            shaderType = GL_FRAGMENT_SHADER;
        }

        shaderId = glCreateShader(shaderType);
    }

    EyerGLShader::~EyerGLShader()
    {
        if(shaderId != 0){
            glDeleteShader(shaderId);
            shaderId = 0;
        }
    }

    int EyerGLShader::Compile()
    {
        if(shaderId == 0){
            return -1;
        }
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

        return 0;
    }
}