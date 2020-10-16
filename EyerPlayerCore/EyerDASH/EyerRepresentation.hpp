#ifndef EYE_LIB_EYERREPRESENTATION_HPP
#define EYE_LIB_EYERREPRESENTATION_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer{
    class EyerRepresentation {
    public:
        EyerRepresentation();
        ~EyerRepresentation();

        EyerRepresentation(const EyerRepresentation & representation);
        EyerRepresentation & operator = (const EyerRepresentation & representation);

        int LoadFromXML(void * node);

        EyerString & GetId();
    private:
        EyerString id;
    };
}

#endif //EYE_LIB_EYERREPRESENTATION_HPP
