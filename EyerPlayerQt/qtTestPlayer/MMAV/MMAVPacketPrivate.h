#pragma once

extern "C" {
#include <libavformat/avformat.h>
}

class MMAVPacketPrivate {
public:
	AVPacket* avpacket = nullptr;
};
