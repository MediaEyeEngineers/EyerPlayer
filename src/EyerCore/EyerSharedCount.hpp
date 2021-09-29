#ifndef EYERLIB_EYERSHAREDCOUNT_HPP
#define EYERLIB_EYERSHAREDCOUNT_HPP

namespace Eyer
{
    class EyerSharedCount
    {
    public:
        EyerSharedCount();
        ~EyerSharedCount();

        long Add();
        long Reduce();
        long Get();
    private:
        long count = 0;
    };
}

#endif //EYERLIB_EYERSHAREDCOUNT_HPP
