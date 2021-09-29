#ifndef	EYER_CORE_STRING_H
#define	EYER_CORE_STRING_H

#include <string>
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
        EyerString(const std::string & str);
        EyerString(const EyerString & str);
        ~EyerString();

        bool IsEmpty() const;

        EyerString & operator = (const EyerString & s);

        bool operator == (const EyerString & s) const;

        bool operator > (const EyerString & s) const;
        bool operator < (const EyerString & s) const;

        const EyerString operator + (const EyerString & s) const;
        const EyerString & operator += (const EyerString & s);

        int Replace(const EyerString & substr, const EyerString & replacement);
        int Split(EyerString * resArr, const EyerString & splitStr);

        static EyerString Sprintf(const EyerString & format, ...);

        static EyerString Number(float num, EyerString format = "%f");
        static EyerString Number(int num, EyerString format = "%d");
        static EyerString Number(uint32_t num, EyerString format = "%d");

        static EyerString Number(long num);
        static EyerString Number(long long num);
        static EyerString Number(uint64_t num);

        static EyerString FormatSec(int sec);

        EyerString ReplaceAll(const EyerString & substr, const EyerString & replacement);

    private:
        std::vector<EyerString> splitVec;
    };
}

#endif
