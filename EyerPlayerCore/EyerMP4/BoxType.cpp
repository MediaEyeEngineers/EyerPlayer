#include "BoxType.hpp"
#include <stdio.h>

namespace Eyer
{
    BoxType BoxType::UNKNOW     (0, 'u', 'n', 'k', 'w', false);
    BoxType BoxType::ROOT       (1, 'r', 'o', 'o', 't', true);
    BoxType BoxType::FTYP       (2, 'f', 't', 'y', 'p', false);
    BoxType BoxType::FREE       (3, 'f', 'r', 'e', 'e', false);
    BoxType BoxType::MOOV       (4, 'm', 'o', 'o', 'v', true);
    BoxType BoxType::MDAT       (5, 'm', 'd', 'a', 't', false);
    BoxType BoxType::MVHD       (6, 'm', 'v', 'h', 'd', false);
    BoxType BoxType::TRAK       (7, 't', 'r', 'a', 'k', true);
    BoxType BoxType::TKHD       (8, 't', 'k', 'h', 'd', false);
    BoxType BoxType::MDIA       (9, 'm', 'd', 'i', 'a', true);
    BoxType BoxType::MINF       (10, 'm', 'i', 'n', 'f', true);
    BoxType BoxType::STBL       (11, 's', 't', 'b', 'l', true);
    BoxType BoxType::EDTS       (12, 'e', 'd', 't', 's', true);
    BoxType BoxType::MDHD       (13, 'm', 'd', 'h', 'd', false);
    BoxType BoxType::MVEX       (14, 'm', 'v', 'e', 'x', true);
    BoxType BoxType::ELST       (15, 'e', 'l', 's', 't', false);
    BoxType BoxType::HDLR       (16, 'h', 'd', 'l', 'r', false);
    BoxType BoxType::DINF       (17, 'd', 'i', 'n', 'f', true);
    BoxType BoxType::DREF       (18, 'd', 'r', 'e', 'f', false);
    BoxType BoxType::URL        (19, 'u', 'r', 'l', ' ', false);
    BoxType BoxType::URN        (20, 'u', 'r', 'n', ' ', false);
    BoxType BoxType::TREX       (21, 't', 'r', 'e', 'x', false);
    BoxType BoxType::MEHD       (22, 'm', 'e', 'h', 'd', false);
    BoxType BoxType::STSD       (23, 's', 't', 's', 'd', false);
    BoxType BoxType::AVC1       (24, 'a', 'v', 'c', '1', false);
    BoxType BoxType::AVCC       (25, 'a', 'v', 'c', 'C', false);
    BoxType BoxType::STTS       (26, 's', 't', 't', 's', false);
    BoxType BoxType::STSC       (27, 's', 't', 's', 'c', false);
    BoxType BoxType::STCO       (28, 's', 't', 'c', 'o', false);
    BoxType BoxType::MOOF       (30, 'm', 'o', 'o', 'f', true);
    BoxType BoxType::MFHD       (32, 'm', 'f', 'h', 'd', false);
    BoxType BoxType::TRAF       (34, 't', 'r', 'a', 'f', true);
    BoxType BoxType::TFHD       (36, 't', 'f', 'h', 'd', false);

    BoxType::BoxType()
    {
        *this = BoxType::UNKNOW;
    }

    BoxType::BoxType(int _id, char _a, char _b, char _c, char _d, bool _hasSub)
    {
        id = _id;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        hasSub = _hasSub;
    }

    BoxType::~BoxType()
    {

    }

    bool BoxType::operator == (const BoxType boxType) const
    {
        return id == boxType.id;
    }

    bool BoxType::operator != (const BoxType boxType) const
    {
        return !(*this == boxType);
    }

    char BoxType::GetA()
    {
        return a;
    }

    char BoxType::GetB()
    {
        return b;
    }

    char BoxType::GetC()
    {
        return c;
    }

    char BoxType::GetD()
    {
        return d;
    }

    uint32_t BoxType::GetABCD()
    {
        uint32_t abcd = 0;

        abcd = d << 24 | c << 16 | b << 8 | a;

        return abcd;
    }

    BoxType BoxType::GetType(uint32_t net_type)
    {
        if(net_type == UNKNOW.GetABCD()){
            return UNKNOW;
        }
        else if(net_type == FTYP.GetABCD()){
            return FTYP;
        }
        else if(net_type == FREE.GetABCD()){
            return FREE;
        }
        else if(net_type == MOOV.GetABCD()){
            return MOOV;
        }
        else if(net_type == MDAT.GetABCD()){
            return MDAT;
        }
        else if(net_type == MVHD.GetABCD()){
            return MVHD;
        }
        else if(net_type == TRAK.GetABCD()){
            return TRAK;
        }
        else if(net_type == TKHD.GetABCD()){
            return TKHD;
        }
        else if(net_type == MDIA.GetABCD()){
            return MDIA;
        }
        else if(net_type == MINF.GetABCD()){
            return MINF;
        }
        else if(net_type == STBL.GetABCD()){
            return STBL;
        }
        else if(net_type == EDTS.GetABCD()) {
            return EDTS;
        }
        else if(net_type == MDHD.GetABCD()) {
            return MDHD;
        }
        else if(net_type == MVEX.GetABCD()) {
            return MVEX;
        }
        else if(net_type == ELST.GetABCD()) {
            return ELST;
        }
        else if(net_type == HDLR.GetABCD()) {
            return HDLR;
        }
        else if(net_type == DINF.GetABCD()) {
            return DINF;
        }
        else if(net_type == DREF.GetABCD()) {
            return DREF;
        }
        else if(net_type == URL.GetABCD()) {
            return URL;
        }
        else if(net_type == URN.GetABCD()) {
            return URN;
        }
        else if(net_type == TREX.GetABCD()) {
            return TREX;
        }
        else if(net_type == MEHD.GetABCD()) {
            return MEHD;
        }
        else if(net_type == STSD.GetABCD()) {
            return STSD;
        }
        else if(net_type == AVC1.GetABCD()) {
            return AVC1;
        }
        else if(net_type == AVCC.GetABCD()) {
            return AVCC;
        }
        else if(net_type == STTS.GetABCD()) {
            return STTS;
        }
        else if(net_type == MOOF.GetABCD()) {
            return MOOF;
        }
        else if(net_type == STSC.GetABCD()) {
            return STSC;
        }
        else if(net_type == STCO.GetABCD()) {
            return STCO;
        }
        else if(net_type == TRAF.GetABCD()) {
            return TRAF;
        }
        else if(net_type == TFHD.GetABCD()) {
            return TFHD;
        }
        else if(net_type == MFHD.GetABCD()) {
            return MFHD;
        }
        return UNKNOW;
    }

    bool BoxType::HasSub()
    {
        return hasSub;
    }

    int BoxType::PrintInfo()
    {
        printf("%c%c%c%c\n", a, b, c, d);
        return 0;
    }
}