#include "EyerRepresentation.hpp"
#include <libxml2/libxml/parser.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerRepresentation::EyerRepresentation()
    {

    }

    EyerRepresentation::~EyerRepresentation()
    {

    }

    EyerRepresentation::EyerRepresentation(const EyerRepresentation & representation)
    {
        *this = representation;
    }

    EyerRepresentation & EyerRepresentation::operator = (const EyerRepresentation & representation)
    {
        id = representation.id;
        return *this;
    }

    int EyerRepresentation::LoadFromXML(void * node)
    {
        xmlNode * representationNode = (xmlNode *)node;
        id = (char *)xmlGetProp(representationNode, BAD_CAST"id");
        return 0;
    }

    EyerString & EyerRepresentation::GetId()
    {
        return id;
    }
}