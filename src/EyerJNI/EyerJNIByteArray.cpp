#include "EyerJNIByteArray.hpp"

namespace Eyer
{
    EyerJNIByteArray::EyerJNIByteArray(EyerJNIEnv * _env, int _len)
    {
        env = _env;
        len = _len;
        array = env->env->NewByteArray(len);
    }

    EyerJNIByteArray::~EyerJNIByteArray()
    {
        if(array != nullptr){
            env->env->DeleteLocalRef(array);
            array = nullptr;
        }
    }

    int EyerJNIByteArray::SetData(uint8_t * data)
    {
        env->env->SetByteArrayRegion(array, 0, len, (jbyte*) data);
        return 0;
    }

    jbyteArray EyerJNIByteArray::GetJObject()
    {
        return array;
    }
}