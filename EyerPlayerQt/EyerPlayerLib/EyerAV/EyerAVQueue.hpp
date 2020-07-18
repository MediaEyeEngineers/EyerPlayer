//
// Created by redknot on 2020/3/29.
//

#ifndef EYE_LIB_EYERAVQUEUE_HPP
#define EYE_LIB_EYERAVQUEUE_HPP

#include <mutex>
#include <queue>

namespace Eyer
{
    template<typename T>
    class EyerAVQueue {
    public:
        EyerAVQueue()
        {

        }

        ~EyerAVQueue()
        {
            mut.lock();
            /*
            while(queue.size() > 0){
                T * t = queue.front();
                queue.pop();
                delete t;
            }
            */

            while(queue.size() > 0){
                T * t = queue.front();
                queue.pop();
            }

            mut.unlock();
        }



        int Lock()
        {
            mut.lock();
            return 0;
        }

        int UnLock()
        {
            mut.unlock();
            return 0;
        }

        int Push(T * t)
        {
            mut.lock();

            queue.push(t);

            mut.unlock();
            return 0;
        }

        int Front(T ** t)
        {
            int ret = -1;
            mut.lock();

            if(queue.size() > 0){
                *t = queue.front();
                ret = 0;
            }

            mut.unlock();
            return ret;
        }

        int FrontPop(T ** t)
        {
            int ret = -1;
            mut.lock();

            if(queue.size() > 0) {
                *t = queue.front();
                queue.pop();
                ret = 0;
            }

            mut.unlock();
            return ret;
        }

        int Size()
        {
            int size = 0;
            mut.lock();

            size = queue.size();

            mut.unlock();

            return size;
        }
    private:
        std::mutex mut;
        std::queue<T *> queue;
    };
}



#endif //EYE_LIB_EYERAVQUEUE_HPP