#include"MMAV.h"

#include"MMAVPacketPrivate.h"

MMAVPacket::MMAVPacket(){
	avpacketPrivate = new MMAVPacketPrivate();
	avpacketPrivate->avpacket = av_packet_alloc();
}

MMAVPacket::~MMAVPacket(){
	if (avpacketPrivate->avpacket != nullptr) {
		av_packet_free(&avpacketPrivate->avpacket);
		avpacketPrivate->avpacket = nullptr;
	}

	if (avpacketPrivate != nullptr) {
		delete avpacketPrivate;
		avpacketPrivate = nullptr;
	}
	
}

int MMAVPacket::getStreamIndex() {
	return avpacketPrivate->avpacket->stream_index;
}

