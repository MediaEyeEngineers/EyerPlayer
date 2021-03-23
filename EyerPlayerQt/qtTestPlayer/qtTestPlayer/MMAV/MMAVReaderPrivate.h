#pragma once

extern "C" {
#include <libavformat/avformat.h>
}

class MMAVReaderPrivate {
public:
	AVFormatContext* avformatContext = nullptr;
};
