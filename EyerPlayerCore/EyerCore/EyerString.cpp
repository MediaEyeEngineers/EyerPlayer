#include "EyerString.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stdarg.h>

namespace Eyer {
    EyerString::EyerString()
    {

    }

    EyerString::EyerString(const EyerString & str)
    {
        *this = str;
    }

    EyerString::~EyerString()
    {
        ClearStr();
    }

    EyerString::EyerString(const char _str[])
    {
        ClearStr();

        if(_str == nullptr){
            return;
        }

        int _strLen = strlen(_str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, _str, _strLen);
    }

    EyerString & EyerString::operator = (const EyerString & s)
    {
        ClearStr();

        if(s.str == nullptr){
            return *this;
        }

        int _strLen = strlen(s.str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, s.str, _strLen);

        return *this;
    }

    bool EyerString::operator == (const EyerString & s)
    {
        if(IsEmpty() && s.IsEmpty()){
            return true;
        }

        if(IsEmpty()){
            return false;
        }

        if(s.IsEmpty()){
            return false;
        }

        if (strcmp(str, s.str) == 0) {
            return true;
        }

        return false;
    }

    bool EyerString::operator > (const EyerString & s)
    {
        if(strcmp(str, s.str) > 0){
            return false;
        }
        return true;
    }

    bool EyerString::operator < (const EyerString & s)
    {
        if(strcmp(str, s.str) < 0){
            return false;
        }
        return true;
    }

    EyerString EyerString::operator + (const EyerString & s){
        EyerString outStr;

        if(IsEmpty() && s.IsEmpty()){
            return outStr;
        }

        int strALen = 0;
        if(!IsEmpty()){
            strALen = strlen(str);
        }

        int strBLen = 0;
        if(!s.IsEmpty()){
            strBLen = strlen(s.str);
        }

        int strLen = strALen + strBLen;
        if(strLen <= 0){
            return outStr;
        }

        // alloc
        outStr.str = (char *)malloc(strLen + 1);
        if(strALen > 0){
            memcpy(outStr.str, str, strALen);
        }

        if(strBLen > 0){
            memcpy(outStr.str + strALen, s.str, strBLen);
        }

        outStr.str[strLen] = '\0';

        return outStr;
    }

    bool EyerString::IsEmpty() const
    {
        if(str == nullptr){
            return true;
        }
        return false;
    }

    int EyerString::ClearStr()
    {
        if(str != nullptr){
            free(str);
            str = nullptr;
        }

        return 0;
    }

    EyerString EyerString::Number(int num, EyerString format)
    {
        char str[1024];

        sprintf(str, format.str, num);

        return str;
    }

    EyerString Number(long num)
    {
        char str[1024];

        sprintf(str, "%ld", num);

        return str;
    }

    EyerString Number(long long num)
    {
        char str[1024];

        sprintf(str, "%lld", num);

        return str;
    }
}
