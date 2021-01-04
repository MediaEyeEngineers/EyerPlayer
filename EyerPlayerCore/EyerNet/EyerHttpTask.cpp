#include "EyerHttpTask.hpp"
#include "EyerHttpTaskPrivate.hpp"

namespace Eyer
{
    size_t EyerHttpTask::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        // EyerLog("size: %d, nmemb: %d, p: %lld\n", size, nmemb, (long long)userp);
        EyerHttpTask * httpTask = (EyerHttpTask *)userp;
        httpTask->SetDate((unsigned char *)buffer, size * nmemb);
        return size * nmemb;
    }

    EyerHttpTask::EyerHttpTask()
    {
        piml = new EyerHttpTaskPrivate();
        piml->hnd = curl_easy_init();

        buffer.Clear();

        curl_easy_setopt(piml->hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2_0);
        curl_easy_setopt(piml->hnd, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(piml->hnd, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(piml->hnd, CURLOPT_PIPEWAIT, 1L);
    }

    EyerHttpTask::~EyerHttpTask()
    {
        if(piml->hnd != nullptr){
            curl_easy_cleanup(piml->hnd);
            piml->hnd = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerHttpTask::SetUrl(EyerString & url)
    {
        curl_easy_setopt(piml->hnd, CURLOPT_URL, url.str);
        return 0;
    }

    int EyerHttpTask::GetBuffer(Eyer::EyerBuffer & _buffer)
    {
        _buffer = buffer;
        return 0;
    }

    int EyerHttpTask::SetDate(unsigned char * data, int dataLen)
    {
        // EyerLog("Len: %d\n", dataLen);
        buffer.Append(data, dataLen);
        // EyerLog("Len: %d\n", buffer.GetBuffer(nullptr));
        return 0;
    }
}