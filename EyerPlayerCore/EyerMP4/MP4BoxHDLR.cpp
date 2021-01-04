#include "MP4BoxHDLR.hpp"

#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxHDLR::MP4BoxHDLR() : MP4FullBox()
    {
        type = BoxType::HDLR;
    }

    MP4BoxHDLR::~MP4BoxHDLR()
    {

    }

    /*
    MP4BoxHDLR & MP4BoxHDLR::operator = (const MP4BoxHDLR & hdlr)
    {
        handle_type_a = hdlr.handle_type_a;
        handle_type_b = hdlr.handle_type_b;
        handle_type_c = hdlr.handle_type_c;
        handle_type_d = hdlr.handle_type_d;

        str = hdlr.str;

        return *this;
    }
     */

    bool MP4BoxHDLR::operator == (const MP4BoxHDLR & hdlr) const
    {
        if(!MP4FullBox::operator==(hdlr)){
            return false;
        }

        if(handle_type_a != hdlr.handle_type_a){
            return false;
        }
        if(handle_type_b != hdlr.handle_type_b){
            return false;
        }
        if(handle_type_c != hdlr.handle_type_c){
            return false;
        }
        if(handle_type_d != hdlr.handle_type_d){
            return false;
        }
        if(!(str == hdlr.str)){
            return false;
        }

        return true;
    }


    EyerBuffer MP4BoxHDLR::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteZero(sizeof(uint32_t));
        stream.WriteBigEndian(handle_type_a);
        stream.WriteBigEndian(handle_type_b);
        stream.WriteBigEndian(handle_type_c);
        stream.WriteBigEndian(handle_type_d);

        stream.WriteZero(sizeof(uint32_t) * 3);

        stream.WriteString(str);

        return stream.GetBuffer();
    }

    int MP4BoxHDLR::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        stream.Skip(sizeof(uint32_t), offset);

        handle_type_a = stream.ReadBigEndian_uint8(offset);
        handle_type_b = stream.ReadBigEndian_uint8(offset);
        handle_type_c = stream.ReadBigEndian_uint8(offset);
        handle_type_d = stream.ReadBigEndian_uint8(offset);

        stream.Skip(sizeof(uint32_t) * 3, offset);

        stream.ReadStr(str, stream.GetBuffer().GetLen());

        return offset;
    }

    int MP4BoxHDLR::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%shandle_type: %c%c%c%c\n", levelStr.str, handle_type_a, handle_type_b, handle_type_c, handle_type_d);
        printf("%sstr: %s\n", levelStr.str, str.str);

        return 0;
    }

    int MP4BoxHDLR::SetDefaultData()
    {
        handle_type_a = 'v';
        handle_type_b = 'i';
        handle_type_c = 'd';
        handle_type_d = 'e';

        str = "VideoHandler";

        type = BoxType::HDLR;
        version = 0;
        size = Serialize().GetLen();

        return 0;
    }
}