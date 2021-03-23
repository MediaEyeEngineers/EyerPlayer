#include"MMAV.h"
#include"MMAVDecoderPrivate.h"
#include"MMAVStreamPrivate.h"
#include"MMAVPacketPrivate.h"
#include"MMAVFreamPrivate.h"


MMAVDecoder::MMAVDecoder() {
	decoderImpl = new MMAVDecoderPrivate();
	decoderImpl->avcodecContext = avcodec_alloc_context3(nullptr);
	
}

MMAVDecoder::~MMAVDecoder() {
	if (decoderImpl->avcodecContext != nullptr) {
		avcodec_free_context(&decoderImpl->avcodecContext);
		decoderImpl->avcodecContext = nullptr;
	}

	if (decoderImpl != nullptr) {
		delete decoderImpl;
		decoderImpl = nullptr;
	}
}

int MMAVDecoder::init(MMAVStream* AVStream){
	

	avcodec_parameters_to_context(decoderImpl->avcodecContext, AVStream->streamPrivate->codecParamet);

	AVCodec * avcodec = avcodec_find_decoder(AVStream->streamPrivate->codecParamet->codec_id);
	int ret = avcodec_open2(decoderImpl->avcodecContext,avcodec,nullptr );
	if (ret != 0) {
		printf("avcodec_open2 fail ==> %d\n", ret);
		return -1;
	}

	return 0;
}

int MMAVDecoder::sendPacket(MMAVPacket* mmavpacket) {
	if (mmavpacket == nullptr) {
		return avcodec_send_packet(decoderImpl->avcodecContext, nullptr);
	}
	else {
		return avcodec_send_packet(decoderImpl->avcodecContext, mmavpacket->avpacketPrivate->avpacket);
	}
	
}

int MMAVDecoder::receiveFream(MMAVFream* mmavFream) {
	return avcodec_receive_frame(decoderImpl->avcodecContext, mmavFream->avFreamPrivate->frame);
}

int MMAVDecoder::close() {
	return avcodec_close(decoderImpl->avcodecContext);
}