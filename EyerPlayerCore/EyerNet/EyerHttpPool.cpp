#include "EyerHttpPool.hpp"

#include "EyerHttpPoolPrivate.hpp"
#include "EyerHttpTaskPrivate.hpp"

namespace Eyer
{
    EyerHttpPool::EyerHttpPool()
    {
        piml = new EyerHttpPoolPrivate();
        piml->multi_handle = curl_multi_init();
        curl_multi_setopt(piml->multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
    }

    EyerHttpPool::~EyerHttpPool()
    {
        if(piml->multi_handle != nullptr){
            curl_multi_cleanup(piml->multi_handle);
            piml->multi_handle = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerHttpPool::AddTask(EyerHttpTask & task)
    {
        curl_multi_add_handle(piml->multi_handle, task.piml->hnd);
        return 0;
    }

    int EyerHttpPool::Start()
    {
        curl_multi_perform(piml->multi_handle, &piml->still_running);
        return 0;
    }

    int EyerHttpPool::Loop()
    {
        curl_multi_perform(piml->multi_handle, &piml->still_running);

        /*
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        long curl_timeo = -1;
        curl_multi_timeout(piml->multi_handle, &curl_timeo);
        if(curl_timeo >= 0) {
            timeout.tv_sec = curl_timeo / 1000;
            if(timeout.tv_sec > 1) {
                timeout.tv_sec = 1;
            }
            else{
                timeout.tv_usec = (curl_timeo % 1000) * 1000;
            }
        }

        fd_set fdread;
        fd_set fdwrite;
        fd_set fdexcep;

        FD_ZERO(&fdread);
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdexcep);

        int maxfd = -1;
        CURLMcode mc = curl_multi_fdset(piml->multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);
        if(mc != CURLM_OK) {
            return -1;
        }

        int rc;
        if(maxfd == -1) {
            struct timeval wait = { 0, 100 * 1000 };
            rc = select(0, NULL, NULL, NULL, &wait);
        }
        else{
            rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
        }

        switch(rc) {
            case -1:
                break;
            case 0:
            default:
                curl_multi_perform(piml->multi_handle, &piml->still_running);
                break;
        }


        struct CURLMsg * m = nullptr;
        do {
            int msgq = 0;
            m = curl_multi_info_read(piml->multi_handle, &msgq);
            if(m && (m->msg == CURLMSG_DONE)) {
                EyerLog("Okay\n");
                CURL * e = m->easy_handle;
                curl_multi_remove_handle(piml->multi_handle, e);

                long response_code = -1L;
                curl_easy_getinfo(e, CURLINFO_RESPONSE_CODE, &response_code);
                printf("response_code: %lld\n", response_code);
            }
        } while(m);
         */

        return 0;
    }

    int EyerHttpPool::StillRunning()
    {
        return piml->still_running;
    }
}
