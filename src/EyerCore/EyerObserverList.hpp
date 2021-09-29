#ifndef EYERLIB_EYEROBSERVERLIST_HPP
#define EYERLIB_EYEROBSERVERLIST_HPP

#include <mutex>
#include <queue>

#include <vector>

#include "EyerSubject.hpp"

namespace Eyer
{
    template<typename T>
    class EyerObserverList : public EyerSubject
    {
    public:
        EyerObserverList()
        {

        }

        ~EyerObserverList()
        {

        }

        void Lock()
        {
            mut.lock();
        }

        void UnLock()
        {
            mut.unlock();
        }

        int Push(const T & t)
        {
            vector.push_back(t);
            NotifyObserver();
            return 0;
        }

        int Get(T & t, int index)
        {
            if(index < 0) {
                return -1;
            }
            if(index >= Size()){
                return -1;
            }

            t = vector[index];
            NotifyObserver();

            return 0;
        }

        int Remove(int index)
        {
            if(index < 0) {
                return -1;
            }
            if(index >= Size()){
                return -1;
            }

            vector.erase(vector.begin() + index);
            NotifyObserver();

            return 0;
        }

        int Size()
        {
            return vector.size();
        }




        int PushLock(const T & t)
        {
            std::lock_guard<std::mutex> lg(mut);
            return Push(t);
        }

        int GetLock(T & t, int index)
        {
            std::lock_guard<std::mutex> lg(mut);
            return Get(t, index);
        }

        int RemoveLock(int index)
        {
            std::lock_guard<std::mutex> lg(mut);
            return Remove(index);
        }

        int SizeLock()
        {
            std::lock_guard<std::mutex> lg(mut);
            return Size();
        }

    private:
        std::mutex mut;
        std::vector<T> vector;
    };
}

#endif //EYERLIB_EYEROBSERVERLIST_HPP
