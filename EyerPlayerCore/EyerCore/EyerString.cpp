#include "EyerString.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stdarg.h>
#include "string_ext.h"

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

    int EyerString::Replace(const EyerString & substr, const EyerString & replacement)
    {
        char outStr[1024 * 128];
        memset(outStr, 0, 2048);

        strrpl(str, outStr, 2048, substr.str, replacement.str);

        *this = outStr;

        return 0;
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

    EyerString EyerString::Number(int num, EyerString format)
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
}
