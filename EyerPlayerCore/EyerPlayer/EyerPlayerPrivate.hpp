#ifndef	EYER_PLAYER_PRIVATE_H
#define	EYER_PLAYER_PRIVATE_H

#include "EyerPlayerEventManager.hpp"
#include "EyerGLRenderTask/YUVRenderTask.hpp"
#include "EyerGLRenderTask/YUVRender.hpp"
#include <string>
#include <jni.h>

namespace Eyer
{
    class EyerPlayerPrivate 
    {
    public:
        EyerPlayerEventManager * eventManager = nullptr;
        std::string url;
        jobject surface = nullptr;
        EyerPlayerConfig playerConfig;

        YUVRenderTask * yuvRenderTask = nullptr;

        YUVRender yuvRender;

        AVFrameQueueManager * frameQueueManager = nullptr;
    };
}

#endif