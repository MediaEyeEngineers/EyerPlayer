#ifndef EYERPLAYER_EYERJNIENVMANAGER_H
#define EYERPLAYER_EYERJNIENVMANAGER_H

#include <jni.h>

namespace Eyer{
    class EyerJNIEnvManager {
    public:
        static JavaVM * jvm;
    };
}



#endif //EYERPLAYER_EYERJNIENVMANAGER_H
