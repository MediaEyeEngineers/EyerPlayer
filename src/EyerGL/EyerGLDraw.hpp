#ifndef EYERLIB_EYERGLDRAW_HPP
#define EYERLIB_EYERGLDRAW_HPP

#include "EyerCore/EyerCore.hpp"

#include "EyerGLShader.hpp"
#include "EyerGLProgram.hpp"
#include "EyerGLTexture.hpp"
#include "EyerGLVAO.hpp"
#include "EyerGLDrawType.hpp"

namespace Eyer
{
    class EyerGLDraw {
    public:
        EyerGLDraw(const EyerString & vertexShader, const EyerString & fragmentShader, OpenGLFunctionsContext * _funcCtx = nullptr);
        ~EyerGLDraw();

        int SetVAO(EyerGLVAO * _vao);

        int Draw(EyerGLDrawType drawType = EyerGLDrawType::TRIANGLES);

        int PutUniform1i(const EyerString & key, int value);
        int PutUniform1f(const EyerString & key, float value);
        int PutMatrix4fv(const EyerString & key, const EatrixF4x4 & _mat);
        int PutMatrix3fv(const EyerString & key, const EatrixF3x3 & _mat);
        int PutTexture(const EyerString & uniform, EyerGLTexture * texture, int textureIndex);

    public:
        EyerGLProgram * program = nullptr;
        EyerGLShader * vertextShader = nullptr;
        EyerGLShader * fragmentShader = nullptr;
        EyerGLVAO * vao = nullptr;

        OpenGLFunctionsContext * funcCtx = nullptr;
    };
}

#endif //EYERLIB_EYERGLDRAW_HPP
