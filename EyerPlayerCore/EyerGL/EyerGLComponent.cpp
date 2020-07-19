#include "EyerGL.hpp"

namespace Eyer
{
    int EyerGLComponent::Viewport(int w, int h)
    {
        width = w;
        height = h;

        return 0;
    }

    EyerGLComponent::~EyerGLComponent()
    {

    }
}