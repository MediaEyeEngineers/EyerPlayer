#ifndef EYERCAMERAANDROID_EYERJNIOBJECT_HPP
#define EYERCAMERAANDROID_EYERJNIOBJECT_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerJNIEnv.hpp"

namespace Eyer
{
    class EyerJNIObject
    {
    public:
        EyerJNIObject(EyerJNIEnv * _env, const EyerString & _clazzName, const EyerString & _methodSig, ...);
        ~EyerJNIObject();

        int CallInt(const EyerString & _methodName, const EyerString & _methodSig, ...);
        void CallVoid(const EyerString & _methodName, const EyerString & _methodSig, ...);
        int64_t CallLong(const EyerString & _methodName, const EyerString & _methodSig, ...);
        jobject CallObject(const EyerString & _methodName, const EyerString & _methodSig, ...);

    private:
        EyerJNIEnv * env = nullptr;

        jclass clazz = nullptr;
        jobject obj = nullptr;
    };
}

#endif //EYERCAMERAANDROID_EYERJNIOBJECT_HPP
