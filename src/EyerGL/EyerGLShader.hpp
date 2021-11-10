#ifndef EYERLIB_EYERGLSHADER_HPP
#define EYERLIB_EYERGLSHADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "OpenGLFunctionsContext.hpp"

namespace Eyer
{
    enum EyerGLShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    class EyerGLShader {
    public:
        EyerGLShader(EyerGLShaderType _type, const EyerString & _src, OpenGLFunctionsContext * _funcCtx = nullptr);
        ~EyerGLShader();

        int Compile();
    public:
        EyerGLShaderType type = EyerGLShaderType::VERTEX_SHADER;
        EyerString src;

        unsigned int shaderId = 0;
    private:
        EyerGLShader(const EyerGLShader & shader) = delete;
        const EyerGLShader & operator = (const EyerGLShader & shader) = delete;

        OpenGLFunctionsContext * funcCtx = nullptr;
    };
}

#endif //EYERLIB_EYERGLSHADER_HPP
