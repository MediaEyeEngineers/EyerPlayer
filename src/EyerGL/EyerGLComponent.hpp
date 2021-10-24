#ifndef EYERLIB_EYERGLCOMPONENT_HPP
#define EYERLIB_EYERGLCOMPONENT_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerGLTexture.hpp"

namespace Eyer
{
    class EyerGLComponent {
    public:
        virtual ~EyerGLComponent();

        virtual int Draw() = 0;
    };
}

#endif //EYERLIB_EYERGLCOMPONENT_HPP
