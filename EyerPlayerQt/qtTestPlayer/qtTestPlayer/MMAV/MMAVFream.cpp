#include "MMAV.h"
#include "MMAVFreamPrivate.h"
#include <malloc.h>
#include <iostream>

extern "C" {
	#include<libavutil/pixdesc.h>
	#include<libavutil/imgutils.h>
	#include <libswscale/swscale.h>
}

MMAVFream::MMAVFream() {
	avFreamPrivate = new MMAVFreamPrivate();
	avFreamPrivate->frame = av_frame_alloc();
}

MMAVFream::~MMAVFream() {
	if (avFreamPrivate->frame != nullptr) {
		av_frame_free(&avFreamPrivate->frame);
		avFreamPrivate->frame = nullptr;
	}

	if (avFreamPrivate != nullptr) {
		delete avFreamPrivate;
		avFreamPrivate = nullptr;
	}

}

void MMAVFream::PrintFream() {
	printf("height: %d \n", avFreamPrivate->frame->height);
	printf("width: %d \n", avFreamPrivate->frame->width);

	AVPixelFormat format = (AVPixelFormat)(avFreamPrivate->frame->format);

	char* str = (char*)malloc(128);
	str = av_get_pix_fmt_string(str, 128, format);

	printf("Sample Format: %s\n", str);

	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		printf("Linesize[%d]: %d\n", i, avFreamPrivate->frame->linesize[i]);
	}

	free(str);
}


long long MMAVFream::getFreamTime() {
	return avFreamPrivate->frame->pts;
}

unsigned char* MMAVFream::getYUVData(int i) {
	
	return avFreamPrivate->frame->data[i];
}

void MMAVFream::setData(int *w, int* h, int* c) {
	*w = avFreamPrivate->frame->width;
	*h = avFreamPrivate->frame->height;
    *c = avFreamPrivate->frame->channels;
}

