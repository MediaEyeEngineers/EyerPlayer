#ifndef EYERPLAYERLIB_YUV_RENDER_TASK_H
#define EYERPLAYERLIB_YUV_RENDER_TASK_H

#include "EyerGL/EyerGL.hpp"

namespace EyerPlayer {
    class YUVRenderTask : public EyerGLRenderTask
    {
    public:
        YUVRenderTask();
        ~YUVRenderTask();
    };
}

#endif // EYERPLAYERLIB_YUV_RENDER_TASK_H