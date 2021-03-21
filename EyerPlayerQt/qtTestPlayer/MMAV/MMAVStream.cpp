#include "MMAV.h"
#include "MMAVStreamPrivate.h"

MMAVStream::MMAVStream() {
	streamPrivate = new MMAVStreamPrivate();
	streamPrivate->codecParamet = avcodec_parameters_alloc();
}

MMAVStream::~MMAVStream() {
	if (streamPrivate->codecParamet != nullptr) {
		avcodec_parameters_free(&streamPrivate->codecParamet);
		streamPrivate->codecParamet = 0;
	}
	if (streamPrivate != nullptr) {
		delete streamPrivate;
		streamPrivate = 0;
	}
}
   
void MMAVStream::setTimeBase(int den, int num) {
	timeBaseDen = den;
	timeBaseNum = num;
}

void MMAVStream::test(int type) {
	if (type == 1) {
		printf("��Ƶ�ı�������: %s\n", avcodec_get_name(streamPrivate->codecParamet->codec_id));
	}else if (type == 2) {
		printf("��Ƶ�ı�������: %s\n", avcodec_get_name(streamPrivate->codecParamet->codec_id));
		printf("��Ƶ��ͨ���� = %d\n", streamPrivate->codecParamet->channels);
		printf("��Ƶ�Ĳ����� = %d\n", streamPrivate->codecParamet->sample_rate);
	}
	
}