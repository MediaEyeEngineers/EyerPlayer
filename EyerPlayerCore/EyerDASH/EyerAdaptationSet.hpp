#ifndef EYE_LIB_EYERADAPTATIONSET_HPP
#define EYE_LIB_EYERADAPTATIONSET_HPP

#include "EyerSegmentTemplate.hpp"
#include "EyerRepresentation.hpp"

namespace Eyer{
    class EyerAdaptationSet {
    public:
        EyerAdaptationSet();
        ~EyerAdaptationSet();

        EyerAdaptationSet(const EyerAdaptationSet & adaptationSet);

        EyerAdaptationSet & operator = (const EyerAdaptationSet & adaptationSet);

        int LoadFromXML(void * node);


        int GetSegmentTemplate(EyerSegmentTemplate & segmentTemplate);
        int SetSegmentTemplate(EyerSegmentTemplate & segmentTemplate);

        int GetRepresentationSize();
        EyerRepresentation & GetRepresentation(int i);

        EyerString & GetContentType();

    private:
        EyerSegmentTemplate segmentTemplate;
        EyerString contentType;
        std::vector<EyerRepresentation *> representationList;
    };
}

#endif //EYE_LIB_EYERADAPTATIONSET_HPP
