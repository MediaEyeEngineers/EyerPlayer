#include "EyerGL.hpp"

namespace Eyer
{
    EyerGLRenderTask::EyerGLRenderTask()
    {

    }

    EyerGLRenderTask::~EyerGLRenderTask()
    {

    }

    int EyerGLRenderTask::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}