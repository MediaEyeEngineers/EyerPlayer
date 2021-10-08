#ifndef EYERLIB_EYEROBSERVERQUEUE_HPP
#define EYERLIB_EYEROBSERVERQUEUE_HPP

#include <mutex>
#include <queue>
#include "EyerSubject.hpp"

namespace Eyer
{
    template<typename T>
    class EyerObserverQueue : public EyerSubject {
    public:
        EyerObserverQueue()
        {

        }

        ~EyerObserverQueue()
        {
            std::lock_guard<std::mutex> lg(mut);
            while(queue.size() > 0){
                T t = queue.front();
                queue.pop();
            }
        }

        int Push(const T & t)
        {
            std::lock_guard<std::mutex> lg(mut);
            queue.push(t);
            NotifyObserver();
            return 0;
        }

        int Front(T & t)
        {
            std::lock_guard<std::mutex> lg(mut);
            int ret = -1;

            if(queue.size() > 0){
                t = queue.front();
                ret = 0;
            }

            return ret;
        }

        int FrontPop(T & t)
        {
            std::lock_guard<std::mutex> lg(mut);
            int ret = -1;

            if(queue.size() > 0) {
                t = queue.front();
                queue.pop();
                ret = 0;
                NotifyObserver();
            }

            return ret;
        }

        int Size()
        {
            std::lock_guard<std::mutex> lg(mut);
            int size = queue.size();
            return size;
        }

    private:
        std::mutex mut;
        std::queue<T> queue;
    };
}


#endif //EYERLIB_EYEROBSERVERQUEUE_HPP
