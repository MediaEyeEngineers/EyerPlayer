#include "EyerJNIObject.hpp"
#include "EyerJNIEnvManager.hpp"

namespace Eyer
{
    EyerJNIObject::EyerJNIObject(EyerJNIEnv * _env, const EyerString & clazzName, const EyerString & _methodSig, ...)
    {
        env = _env;

        clazz = Eyer::EyerJNIEnvManager::FindClazz(env, clazzName.str);
        if(clazz == nullptr){
            EyerLog("EyerJNIObject FindClass Fail\n");
            return;
        }

        jmethodID init = env->env->GetMethodID(clazz, "<init>", _methodSig.str);
        if(init == nullptr){
            EyerLog("EyerJNIObject GetMethodID Fail\n");
            env->env->DeleteLocalRef(clazz);
            return;
        }

        va_list args;
        va_start(args, _methodSig);
        jobject clazzobj = env->env->NewObjectV(clazz, init, args);
        va_end(args);

        if(clazzobj == nullptr){
            EyerLog("EyerJNIObject NewObject Fail\n");
            env->env->DeleteLocalRef(clazz);
            return;
        }

        obj = env->env->NewGlobalRef(clazzobj);

        env->env->DeleteLocalRef(clazzobj);
    }

    EyerJNIObject::~EyerJNIObject()
    {
        if(obj != nullptr){
            env->env->DeleteGlobalRef(obj);
            obj = nullptr;
        }

        if(clazz != nullptr){
            env->env->DeleteLocalRef(clazz);
            clazz = nullptr;
        }
    }


    int EyerJNIObject::CallInt(const EyerString & _methodName, const EyerString & _methodSig, ...)
    {
        jmethodID methodId = env->env->GetMethodID(clazz, _methodName.str, _methodSig.str);
        if(methodId == nullptr){
            EyerLog("EyerJNIObject GetMethodID Fail\n");
        }

        va_list args;
        va_start(args, _methodSig);
        int ret = env->env->CallIntMethodV(obj, methodId, args);
        va_end(args);

        return ret;
    }

    void EyerJNIObject::CallVoid(const EyerString & _methodName, const EyerString & _methodSig, ...)
    {
        jmethodID methodId = env->env->GetMethodID(clazz, _methodName.str, _methodSig.str);
        if(methodId == nullptr){
            EyerLog("EyerJNIObject GetMethodID Fail\n");
        }

        va_list args;
        va_start(args, _methodSig);
        env->env->CallVoidMethodV(obj, methodId, args);
        va_end(args);
    }

    int64_t EyerJNIObject::CallLong(const EyerString & _methodName, const EyerString & _methodSig, ...)
    {
        jmethodID methodId = env->env->GetMethodID(clazz, _methodName.str, _methodSig.str);
        if(methodId == nullptr){
            EyerLog("EyerJNIObject GetMethodID Fail\n");
        }

        va_list args;
        va_start(args, _methodSig);
        int64_t ret = env->env->CallLongMethodV(obj, methodId, args);
        va_end(args);

        return ret;
    }

    jobject EyerJNIObject::CallObject(const EyerString & _methodName, const EyerString & _methodSig, ...)
    {
        jmethodID methodId = env->env->GetMethodID(clazz, _methodName.str, _methodSig.str);
        if(methodId == nullptr){
            EyerLog("EyerJNIObject GetMethodID Fail\n");
        }

        va_list args;
        va_start(args, _methodSig);
        jobject ret = env->env->CallObjectMethodV(obj, methodId, args);
        va_end(args);

        return ret;
    }
}