//
// Created by redknot on 2020/4/5.
//

#ifndef EYE_LIB_EYERAVQUEUE_MANAGER_HPP
#define EYE_LIB_EYERAVQUEUE_MANAGER_HPP

#include <map>
#include <string>
#include <mutex>

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    template<typename T>
    class EyerAVQueueManager {
    public:
        EyerAVQueueManager()
        {

        }

        ~EyerAVQueueManager()
        {

        }

        int GetQueue(EyerString _key, T * * _t)
        {
            mut.lock();

            std::string key = std::string(_key.str);

            typename std::map<std::string, T *>::iterator it = manager.find(key);
            if(it == manager.end()){
                // 没找到
                T * t = new T();
                *_t = t;

                manager.insert(std::pair<std::string, T *>(key, t));
            }
            else{
                // 找到了
                *_t = it->second;
            }

            mut.unlock();

            return 0;
        }

    private:
        std::map<std::string, T *> manager;
        std::mutex mut;
    };
}

#endif //EYE_LIB_EYERAVQUEUE_MANAGER_HPP