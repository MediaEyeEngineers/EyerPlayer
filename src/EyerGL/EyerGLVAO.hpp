#ifndef EYERLIB_EYERGLVAO_HPP
#define EYERLIB_EYERGLVAO_HPP

#include <vector>
#include "EyerGLDrawType.hpp"
#include "OpenGLFunctionsContext.hpp"

namespace Eyer
{
    class EyerGLVAO {
    public:
        EyerGLVAO(OpenGLFunctionsContext * _funcCtx = nullptr);
        ~EyerGLVAO();

        int AddVBO(float * VBOdata, int bufferSize, int layout, int size = 3, unsigned int stride = 0);
        int SetEBO(unsigned int * EBOdata, int bufferSize);

        int DrawVAO(EyerGLDrawType drawType);

    public:
        unsigned int VAOId = 0;
        unsigned int EBOId = 0;
        int drawTime = 0;
        std::vector<unsigned int> vboList;

    private:
        EyerGLVAO(const EyerGLVAO & vao) = delete;
        const EyerGLVAO & operator = (const EyerGLVAO & vao) = delete;

        OpenGLFunctionsContext * funcCtx = nullptr;
    };
}

#endif //EYERLIB_EYERGLVAO_HPP
