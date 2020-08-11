#include "EyerJNIEnvManager.h"


namespace Eyer{
    JavaVM * EyerJNIEnvManager::jvm = nullptr;
    jobject EyerJNIEnvManager::eyerMediaCodec_ClassLoader = nullptr;
}