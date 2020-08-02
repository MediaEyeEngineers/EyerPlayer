#ifndef	EYER_PLAYER_EVENT_TYPE_H
#define	EYER_PLAYER_EVENT_TYPE_H

namespace EyerPlayer {
    class EventType
    {
    public:
        static const int OPENRequest                        = 101;
        static const int OPENResponse                       = 201;

        static const int STOPRequest                        = 102;
        static const int STOPResponse                       = 202;

        static const int UPDATEUIRequest                    = 103;
        static const int UPDATEUIResponse                   = 203;

        static const int UPDATEAUDIORequest                 = 104;
        static const int UPDATEAUDIOResponse                = 204;


        static const int PLAYRequest                        = 105;
        static const int PLAYResponse                       = 205;

        static const int PAUSERequest                       = 106;
        static const int PAUSEResponse                      = 206;

        static const int PROGRESSRequest                    = 107;
        static const int PROGRESSResponse                   = 207;

        static const int SEEKRequest                        = 108;
        static const int SEEKResponse                       = 208;



        static const int LAGStartRequest                    = 109;
        static const int LAGStartResponse                   = 209;

        static const int LAGStopRequest                     = 110;
        static const int LAGStopResponse                    = 210;





        static const int SetGLCtxRequest                    = 111;
        static const int SetGLCtxResponse                   = 211;
    };
}

#endif