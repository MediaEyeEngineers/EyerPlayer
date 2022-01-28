#ifndef	EYER_LIB_GL_TEST_COMPONENT_AV_H
#define	EYER_LIB_GL_TEST_COMPONENT_AV_H

#include "EyerGL/EyerGL.hpp"

namespace Eyer
{
    class EyerGLTestComponent : public EyerGLComponent
    {
    public:
        EyerGLTestComponent();
        ~EyerGLTestComponent();

        virtual int Draw();

        int SetTime(int iTime);
        int SetWH(int w, int h);

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        int width = 0;
        int height = 0;
        int iTime = 0;
    };
}

#endif //EYER_LIB_GL_TEST_COMPONENT_AV_H