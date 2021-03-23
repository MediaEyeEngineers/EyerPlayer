#pragma once

extern "C" {
#include <libavformat/avformat.h>
}

class MMAVFreamPrivate {
public:
	AVFrame* frame = 0;
};
