#ifndef	EYER_CORE_STRING_H
#define	EYER_CORE_STRING_H

namespace Eyer {
    class EyerString
    {
    public:
        char * str = nullptr;
        int ClearStr();

    public:
        EyerString();
        EyerString(const char str[]);
        EyerString(const EyerString & str);
        ~EyerString();

        bool IsEmpty() const;

        EyerString & operator = (const EyerString & s);
        bool operator == (const EyerString & s);

        bool operator > (const EyerString & s);
        bool operator < (const EyerString & s);

        EyerString operator + (const EyerString & s);

        static EyerString Number(int num, EyerString format = "%d");

        static EyerString Number(long num);
        static EyerString Number(long long num);
    };
}

#endif
