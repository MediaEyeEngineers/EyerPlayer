#ifndef EYERLIB_EYERGLPROGRAM_HPP
#define EYERLIB_EYERGLPROGRAM_HPP

#include "EyerGLShader.hpp"

#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    class EyerGLProgram {
    public:
        EyerGLProgram(OpenGLFunctionsContext * _funcCtx = nullptr);
        ~EyerGLProgram();

        int AttachShader(EyerGLShader * shader);
        int LinkProgram();

        int UseProgram();

        int PutUniform1i(const EyerString & key, int value);
        int PutUniform1f(const EyerString & key, float value);
        int PutMatrix4fv(const EyerString & key, const EatrixF4x4 & _mat);
        int PutMatrix3fv(const EyerString & key, const EatrixF3x3 & _mat);

    public:
        unsigned int programId = 0;

    private:
        EyerGLProgram(const EyerGLProgram & program) = delete;
        const EyerGLProgram & operator = (const EyerGLProgram & program) = delete;

        EatrixF4x4 m4;
        float m4data[16];

        float m3data[9];

        OpenGLFunctionsContext * funcCtx = nullptr;
    };
}

#endif //EYERLIB_EYERGLPROGRAM_HPP
