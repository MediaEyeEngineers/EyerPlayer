#ifndef EYE_LIB_EYERMPD_HPP
#define EYE_LIB_EYERMPD_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAdaptationSet.hpp"

namespace Eyer{
    class EyerMPD {
    public:
        EyerMPD();
        ~EyerMPD();

        int SetBaseURL(EyerString & baseURL);

        int LoadMPD(EyerBuffer & buffer);

        int PrintInfo();

        int GetInitURL(EyerString & url, int representationIndex);
        int GetVideoURL(EyerString & url, int number, int representationIndex);

        int GetVideoAdaptationSet(EyerAdaptationSet & videoAdaptationSet);
        int GetAudioAdaptationSet(EyerAdaptationSet & audioAdaptationSet);
    private:
        EyerString baseUrl;
        std::vector<EyerAdaptationSet *> adaptationSetList;
    };
}

#endif //EYE_LIB_EYERMPD_HPP
