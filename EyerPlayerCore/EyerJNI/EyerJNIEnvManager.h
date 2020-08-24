#ifndef EYERPLAYER_EYERJNIENVMANAGER_H
#define EYERPLAYER_EYERJNIENVMANAGER_H

#include <jni.h>

namespace Eyer{
    class EyerJNIEnvManager {
    public:
        static JavaVM * jvm;
        static jobject eyerMediaCodec_ClassLoader;
        static jobject eyerCallback_ClassLoader;

        static JNIEnv * AttachCurrentThread();
    };
}



#endif //EYERPLAYER_EYERJNIENVMANAGER_H
