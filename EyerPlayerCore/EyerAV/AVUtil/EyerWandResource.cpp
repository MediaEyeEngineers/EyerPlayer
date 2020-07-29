#include "AVUtil.hpp"

namespace Eyer
{
    EyerWandResource::EyerWandResource()
    {

    }

    EyerWandResource::~EyerWandResource()
    {

    }

    int EyerWandResource::SetPath(EyerString _resPath)
    {
        resPath = _resPath;
        return 0;
    }
}