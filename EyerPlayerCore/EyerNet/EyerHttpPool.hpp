#ifndef EYE_LIB_EYERHTTPPOOL_HPP
#define EYE_LIB_EYERHTTPPOOL_HPP

#include "EyerHttpTask.hpp"

namespace Eyer{
    class EyerHttpPoolPrivate;

    class EyerHttpPool {
    public:
        EyerHttpPool();
        ~EyerHttpPool();

        int Start();
        int Loop();

        int AddTask(EyerHttpTask & task);

        int StillRunning();
    private:
        EyerHttpPoolPrivate * piml = nullptr;
    };
}

#endif //EYE_LIB_EYERHTTPPOOL_HPP
