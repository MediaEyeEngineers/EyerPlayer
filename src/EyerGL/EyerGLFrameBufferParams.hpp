#ifndef EYERLIB_EYERGLFRAMEBUFFERPARAMS_HPP
#define EYERLIB_EYERGLFRAMEBUFFERPARAMS_HPP

#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    class EyerGLFrameBufferParams
    {
    public:
        EyerGLFrameBufferParams();
        EyerGLFrameBufferParams(int width, int height);
        ~EyerGLFrameBufferParams();

        int width = 0;
        int height = 0;

        EectorF4 color;
    };
}

#endif //EYERLIB_EYERGLFRAMEBUFFERPARAMS_HPP
