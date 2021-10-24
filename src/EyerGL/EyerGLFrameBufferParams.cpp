#include "EyerGLFrameBufferParams.hpp"

namespace Eyer {
    EyerGLFrameBufferParams::EyerGLFrameBufferParams()
    {
        color.SetX(1.0);
        color.SetY(1.0);
        color.SetZ(1.0);
        color.SetW(1.0);
    }

    EyerGLFrameBufferParams::EyerGLFrameBufferParams(int _width, int _height)
    {
        width = _width;
        height = _height;

        color.SetX(1.0);
        color.SetY(1.0);
        color.SetZ(1.0);
        color.SetW(1.0);
    }

    EyerGLFrameBufferParams::~EyerGLFrameBufferParams()
    {

    }
}