#pragma once

extern "C" {
#include <libavformat/avformat.h>
}

class MMAVStreamPrivate {
public:
	AVCodecParameters* codecParamet = nullptr;
};
