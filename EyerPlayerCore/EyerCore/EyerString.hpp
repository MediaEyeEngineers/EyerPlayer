#ifndef	EYER_CORE_STRING_H
#define	EYER_CORE_STRING_H

#include <vector>

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


        bool operator == (const EyerString & s) const;

        bool operator > (const EyerString & s) const;
        bool operator < (const EyerString & s) const;

        EyerString operator + (const EyerString & s);

        int Replace(const EyerString & substr, const EyerString & replacement);
        int Split(EyerString * resArr, const EyerString & splitStr);


        static EyerString Number(int num, EyerString format = "%d");

        static EyerString Number(long num);
        static EyerString Number(long long num);

    private:
        std::vector<EyerString> splitVec;
    };
}

#endif
