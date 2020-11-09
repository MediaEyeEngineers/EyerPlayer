#include "MP4Box.hpp"
#include "MP4BoxFTYP.hpp"
#include "MP4BoxMVHD.hpp"
#include "MP4BoxTKHD.hpp"
#include "MP4BoxELST.hpp"
#include "MP4BoxHDLR.hpp"
#include "MP4BoxDREF.hpp"
#include "MP4BoxURL.hpp"
#include "MP4BoxURN.hpp"
#include "MP4BoxTREX.hpp"
#include "MP4BoxMEHD.hpp"
#include "MP4BoxSTSD.hpp"
#include "MP4BoxSTTS.hpp"
#include "MP4BoxSTSC.hpp"
#include "MP4BoxSTCO.hpp"
#include "MP4BoxMDHD.hpp"
#include "MP4BoxMFHD.hpp"
#include "MP4BoxTFHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4Box::MP4Box()
    {
        type = BoxType::ROOT;
    }

    MP4Box::MP4Box(BoxType _type)
    {
        type = _type;
    }

    MP4Box::MP4Box(const MP4Box & box)
    {
        *this = box;
    }

    MP4Box::~MP4Box()
    {
        for(int i=0;i<subBoxList.size();i++){
            delete subBoxList[i];
        }
        subBoxList.clear();
    }

    MP4Box & MP4Box::operator = (const MP4Box & box)
    {
        type = box.type;
        size = box.size;
        for(int i=0;i<box.subBoxList.size();i++){
            MP4Box * b = CopyBox(box.subBoxList[i]);
            subBoxList.push_back(b);
        }
        return *this;
    }

    bool MP4Box::operator == (const MP4Box & box) const
    {
        if(size != box.size) {
            return false;
        }
        if(type != box.type) {
            return false;
        }

        return true;
    }

    EyerBuffer MP4Box::Serialize()
    {
        EyerBuffer buffer;

        EyerBuffer contentBuffer;
        if(type.HasSub()){
            contentBuffer = SerializeSubBox();
        }
        else{
            contentBuffer = SerializeParam();
        }

        uint8_t head[8];
        int len = contentBuffer.GetLen() + 8;
        head[0] = *((uint8_t *)(&len) + 3);
        head[1] = *((uint8_t *)(&len) + 2);
        head[2] = *((uint8_t *)(&len) + 1);
        head[3] = *((uint8_t *)(&len) + 0);

        head[4] = type.GetA();
        //printf("~~~~~~~~~~~type.GetA():%c\n", type.GetA());
        head[5] = type.GetB();
        head[6] = type.GetC();
        head[7] = type.GetD();

        buffer.Append(head, 8);
        buffer.Append(contentBuffer);
        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);
        /*for(int i=0; i<buffer.GetLen(); i++){
            printf("buffer: %d", data[i]);
        }*/
        return buffer;
    }

    EyerBuffer MP4Box::SerializeSubBox()
    {
        EyerBuffer buffer;
        for(int i=0;i<subBoxList.size();i++){
            EyerBuffer b = subBoxList[i]->Serialize();
            buffer.Append(b);
        }
        return buffer;
    }

    EyerBuffer MP4Box::SerializeParam()
    {
        EyerBuffer buffer;
        return buffer;
    }

    int MP4Box::Parse(EyerBuffer & buffer)
    {
        int offset = 0;

        MP4Stream stream(buffer);
        size = stream.ReadBigEndian_int32(offset);

        type = BoxType::GetType(stream.Read_uint32(offset));

        if(size == 1){
            size = stream.ReadBigEndian_int64(offset);
        }

        // type.PrintInfo();
        if(type.HasSub()){
            EyerBuffer b = buffer;
            EyerBuffer tb;
            b.CutOff(tb, 8);
            ParseSubBox(b, 0);
        }
        else{
            ParseParam(buffer, 8);
        }

        return 0;
    }

    int MP4Box::ParseSubBox(EyerBuffer & buffer, int _offset)
    {
        EyerBuffer tempBuffer = buffer;

        MP4Stream stream(buffer);
        stream.Skip(_offset);

        while (tempBuffer.GetLen() > 0) {
            int offset = 0;
            uint64_t boxSize = stream.ReadBigEndian_uint32(offset);
            BoxType boxtype = BoxType::GetType(stream.Read_uint32(offset));
            if(boxSize == 1){
                boxSize = stream.ReadBigEndian_uint64(offset);
            }

            EyerBuffer boxBuffer;
            tempBuffer.CutOff(boxBuffer, (int)boxSize);

            stream.Skip(boxSize - offset);

            MP4Box * box = CreatBox(boxtype);
            if(box != nullptr){
                box->Parse(boxBuffer);
                subBoxList.push_back(box);
            }
        }
        return _offset;
    }

    int MP4Box::ParseParam(EyerBuffer & buffer, int offset)
    {
        return offset;
    }

    uint64_t MP4Box::GetSize()
    {
        return size;
    }

    BoxType MP4Box::GetType()
    {
        return type;
    }

    MP4Box * MP4Box::GetSubBoxPtr(BoxType type)
    {
        MP4Box * subBox = nullptr;
        for(int i=0;i<subBoxList.size();i++){
            if(subBoxList[i]->type == type){
                subBox = subBoxList[i];
            }
        }
        return subBox;
    }

    int MP4Box::AddSubBox(MP4Box * box)
    {
        MP4Box * subBox = CopyBox(box);
        subBoxList.push_back(subBox);
        return 0;
    }

    int MP4Box::AddSubBox(MP4Box & box)
    {
        return AddSubBox(&box);
    }

    int MP4Box::PrintInfo(int level)
    {
        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }

        printf("%s[%c%c%c%c] (%d bytes)\n", levelStr.str, type.GetA(), type.GetB(), type.GetC(), type.GetD(), size);
        if(type.HasSub()){
            for(int i=0;i<subBoxList.size();i++){
                MP4Box * box = subBoxList[i];
                box->PrintInfo(level + 1);
            }
        }
        return 0;
    }

    MP4Box * MP4Box::CreatBox(BoxType type)
    {
        MP4Box * box = nullptr;
        if(type.HasSub()){
            box = new MP4Box();
        }
        else{
            if(type == BoxType::FTYP){
                box = new MP4BoxFTYP();
            }
            else if(type == BoxType::MVHD){
                box = new MP4BoxMVHD();
            }
            else if(type == BoxType::TKHD){
                box = new MP4BoxTKHD();
            }
            else if(type == BoxType::ELST){
                box = new MP4BoxELST();
            }
            else if(type == BoxType::HDLR){
                box = new MP4BoxHDLR();
            }
            else if(type == BoxType::DREF){
                box = new MP4BoxDREF();
            }
            else if(type == BoxType::URL){
                box = new MP4BoxURL();
            }
            else if(type == BoxType::URN){
                box = new MP4BoxURN();
            }
            else if(type == BoxType::TREX){
                box = new MP4BoxTREX();
            }
            else if(type == BoxType::MEHD){
                box = new MP4BoxMEHD();
            }
            else if(type == BoxType::STSD){
                box = new MP4BoxSTSD();
            }
            else if(type == BoxType::STTS){
                box = new MP4BoxSTTS();
            }
            else if(type == BoxType::STSC){
                box = new MP4BoxSTSC();
            }
            else if(type == BoxType::STCO){
                box = new MP4BoxSTCO();
            }
            else if(type == BoxType::MDHD){
                box = new MP4BoxMDHD();
            }
            else if(type == BoxType::MFHD){
                box = new MP4BoxMFHD();
            }
            else if(type == BoxType::TFHD){
                box = new MP4BoxTFHD();
            }
        }

        return box;
    }
    MP4Box * MP4Box::CopyBox(MP4Box * box)
    {
        MP4Box * dest = CreatBox(box->type);
        if(box->type == BoxType::FTYP){
            *(MP4BoxFTYP *)dest = *(MP4BoxFTYP *)box;
        }
        else if(box->type == BoxType::MVHD){
            *(MP4BoxMVHD *)dest = *(MP4BoxMVHD *)box;
        }
        else if(box->type == BoxType::MEHD){
            *(MP4BoxMEHD *)dest = *(MP4BoxMEHD *)box;
        }
        else if(box->type == BoxType::TREX){
            *(MP4BoxTREX *)dest = *(MP4BoxTREX *)box;
        }
        else if(box->type == BoxType::HDLR){
            *(MP4BoxHDLR *)dest = *(MP4BoxHDLR *)box;
        }
        else if(box->type == BoxType::TKHD){
            *(MP4BoxTKHD *)dest = *(MP4BoxTKHD *)box;
        }
        else if(box->type == BoxType::ELST){
            *(MP4BoxELST *)dest = *(MP4BoxELST *)box;
        }
        else if(box->type == BoxType::DREF){
            *(MP4BoxDREF *)dest = *(MP4BoxDREF *)box;
        }
        else if(box->type == BoxType::STSD){
            *(MP4BoxSTSD *)dest = *(MP4BoxSTSD *)box;
        }
        else if(box->type == BoxType::STTS){
            *(MP4BoxSTTS *)dest = *(MP4BoxSTTS *)box;
        }
        else if(box->type == BoxType::STSC){
            *(MP4BoxSTSC *)dest = *(MP4BoxSTSC *)box;
        }
        else if(box->type == BoxType::STCO){
            *(MP4BoxSTCO *)dest = *(MP4BoxSTCO *)box;
        }
        else if(box->type == BoxType::MDHD){
            *(MP4BoxMDHD *)dest = *(MP4BoxMDHD *)box;
        }
        else if(box->type == BoxType::MFHD){
            *(MP4BoxMFHD *)dest = *(MP4BoxMFHD *)box;
        }
        else if(box->type == BoxType::TFHD){
            *(MP4BoxTFHD *)dest = *(MP4BoxTFHD *)box;
        }
        else{
            *dest = *box;
        }

        return dest;
    }
}