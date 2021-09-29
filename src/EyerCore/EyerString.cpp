#include "EyerString.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <string>
#include <stdarg.h>
#include "string_ext.h"
#include <stdarg.h>

namespace Eyer {
    EyerString::EyerString()
    {

    }

    EyerString::EyerString(const EyerString & str) : EyerString()
    {
        *this = str;
    }

    EyerString::~EyerString()
    {
        ClearStr();
    }

    EyerString::EyerString(const char _str[])
    {
        if(_str == nullptr){
            return;
        }

        ClearStr();

        int _strLen = strlen(_str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, _str, _strLen);
    }

    EyerString::EyerString(const std::string & str)
        : EyerString(str.c_str())
    {
    }

    EyerString & EyerString::operator = (const EyerString & s)
    {
        if(this == &s){
            return *this;
        }

        if(s.str == nullptr){
            return *this;
        }

        ClearStr();

        int _strLen = strlen(s.str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, s.str, _strLen);

        return *this;
    }

    bool EyerString::operator == (const EyerString & s) const
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

    bool EyerString::operator > (const EyerString & s) const
    {
        if(strcmp(str, s.str) > 0){
            return true;
        }
        return false;
    }

    bool EyerString::operator < (const EyerString & s) const
    {
        if(strcmp(str, s.str) < 0){
            return true;
        }
        return false;
    }

    const EyerString EyerString::operator + (const EyerString & s) const{
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

    const EyerString & EyerString::operator += (const EyerString & s)
    {
        *this = *this + s;
        return *this;
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

    int EyerString::Replace(const EyerString & substr, const EyerString & replacement)
    {
        char outStr[1024 * 128];
        memset(outStr, 0, 2048);

        strrpl(str, outStr, 2048, substr.str, replacement.str);

        *this = outStr;

        return 0;
    }

    EyerString EyerString::ReplaceAll(const EyerString & substr, const EyerString & replacement)
    {
        std::string a = str;

        std::string b = substr.str;
        std::string c = replacement.str;

        int pos;
        pos = a.find(b);
        while (pos != -1) {
            a.replace(pos,b.length(),c);
            pos = a.find(b);
        }

        *this = a.c_str();
        return *this;
    }


    int EyerString::Split(EyerString * resArr, const EyerString & splitStr)
    {
        if(resArr == nullptr){
            EyerString temp = *this;

            splitVec.clear();

            char * p = strtok(temp.str, splitStr.str);
            splitVec.push_back(p);

            while(p != NULL){
                p = strtok(NULL, splitStr.str);
                if(p == NULL){
                    break;
                }
                splitVec.push_back(p);
            }
        }
        else {
            for(int i=0;i<splitVec.size();i++){
                resArr[i] = splitVec[i];
            }
        }

        return splitVec.size();
    }

    EyerString EyerString::Number(float num, EyerString format)
    {
        char str[1024];

        sprintf(str, format.str, num);

        return str;
    }

    EyerString EyerString::Number(int num, EyerString format)
    {
        char str[1024];

        sprintf(str, format.str, num);

        return str;
    }

    EyerString EyerString::Number(uint32_t num, EyerString format)
    {
        char str[1024];

        sprintf(str, format.str, num);

        return str;
    }

    EyerString EyerString::Number(long num)
    {
        char str[1024];

        sprintf(str, "%ld", num);

        return str;
    }

    EyerString EyerString::Number(long long num)
    {
        char str[1024];

        sprintf(str, "%lld", num);

        return str;
    }

    EyerString EyerString::Number(uint64_t num)
    {
        char str[1024];

        sprintf(str, "%lld", num);

        return str;
    }

    EyerString EyerString::FormatSec(int sec)
    {
        int s = sec % 60;
        int m = sec / 60 % 60;
        int h = sec / 60 / 60;

        char str[1024];

        sprintf(str, "%02d:%02d:%02d", h, m, s);

        EyerString strRes = str;

        return str;
    }

    EyerString EyerString::Sprintf(const EyerString & format, ...)
    {
        char logStr[4096];
        memset(logStr, 0, 4096);

        va_list args;
        va_start(args, format);
        vsnprintf(logStr, 4096, format.str, args);
        va_end(args);

        return logStr;
    }
}
