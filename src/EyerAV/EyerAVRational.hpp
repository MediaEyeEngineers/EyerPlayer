#ifndef EYERLIB_EYERAVRATIONAL_HPP
#define EYERLIB_EYERAVRATIONAL_HPP

namespace Eyer
{
    class EyerAVRational {
    public:
        EyerAVRational();
        EyerAVRational(int _num, int _den);
        ~EyerAVRational();

        EyerAVRational(const EyerAVRational & rational);
        EyerAVRational & operator = (const EyerAVRational & rational);

    public:
        int num = 0;
        int den = 0;
    };
}

#endif //EYERLIB_EYERAVRATIONAL_HPP
