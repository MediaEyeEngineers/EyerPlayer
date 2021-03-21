#include "MMAV.h"

#include"MMAVReaderPrivate.h"
#include"MMAVPacketPrivate.h"
#include"MMAVStreamPrivate.h"

MMAVReader::MMAVReader() {
	readerPrivate = new MMAVReaderPrivate();
	readerPrivate->avformatContext = avformat_alloc_context();
}

MMAVReader::~MMAVReader() {
	if (readerPrivate->avformatContext != nullptr) {
		avformat_free_context(readerPrivate->avformatContext);
		readerPrivate->avformatContext = nullptr;
	}

	if (readerPrivate != nullptr) {
		delete readerPrivate;
		readerPrivate = nullptr;
	}
	
}


int MMAVReader::open(const char * path, int startTimePlay) {
	if (readerPrivate->avformatContext == nullptr) {
		return -1;
	}
	

	int ret = avformat_open_input(&readerPrivate->avformatContext, path, nullptr, nullptr);
	// 0 is success
	av_dump_format(readerPrivate->avformatContext, 0, path, 0);
	
	long tduration = readerPrivate->avformatContext->duration;         //�����ȡ����΢�룬��Ҫת����
	     

	printf("��Ƶʱ��Ϊ%d��\n", tduration / 1000000);
	

	if (ret==0) {
		av_seek_frame(readerPrivate->avformatContext, -1, startTimePlay* AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
		avformat_find_stream_info(readerPrivate->avformatContext, nullptr);
	}

	return ret;
}

int MMAVReader::getVideo() {
	int video_stream_idx = av_find_best_stream(readerPrivate->avformatContext, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
	long tduration = readerPrivate->avformatContext->streams[video_stream_idx]->duration;
	//// ����������֡��
	//printf("video nb_frames: %lld\n", readerPrivate->avformatContext->streams[video_stream_idx]->nb_frames);
	//// ��������
	//printf("video codec_id: %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->codec_id);
	//printf("video codec_name: %s\n", avcodec_get_name(readerPrivate->avformatContext->streams[video_stream_idx]->codec->codec_id));
	//// ͼ��Ŀ�߳ߴ磬�����в�һ�����ڸ���Ϣ�����ɽ���󸲸�
	//printf("video width x height: %d x %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->width, readerPrivate->avformatContext->streams[video_stream_idx]->codec->height);
	//// ԭʼͼ��ĸ�ʽ�������в�һ�����ڸ���Ϣ�����ɽ���󸲸�
	//printf("video pix_fmt: %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->pix_fmt);
	//// ������
	//printf("video bitrate %lld kb/s\n", (int64_t)readerPrivate->avformatContext->streams[video_stream_idx]->codec->bit_rate / 1000);
	//// ƽ������
	//printf("video avg_frame_rate: %d fps\n", readerPrivate->avformatContext->streams[video_stream_idx]->avg_frame_rate.num / readerPrivate->avformatContext->streams[video_stream_idx]->avg_frame_rate.den);

	return video_stream_idx;
}

int MMAVReader::getAudio() {
	int audio_stream_idx = av_find_best_stream(readerPrivate->avformatContext, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
	AVStream* audiostream = readerPrivate->avformatContext->streams[audio_stream_idx];
	//// ��������
	//printf("audio codec_id: %d\n", audiostream->codec->codec_id);
	//printf("audio codec_name: %s\n", avcodec_get_name(audiostream->codec->codec_id));
	//// ��Ƶ�Ĳ�����
	//printf("audio sample_rate: %d\n", audiostream->codec->sample_rate);
	//// ��Ƶ��ͨ����
	//printf("audio channels: %d\n", audiostream->codec->channels);
	//// ��Ƶ�ĸ�ʽ��λ��
	//printf("audio sample_fmt: %d\n", audiostream->codec->sample_fmt);
	//// ÿ����Ƶ֡�� sample ����
	//printf("audio frame_size: %d\n", audiostream->codec->frame_size);
	//// ����������֡��
	//printf("audio nb_frames: %lld\n", audiostream->nb_frames);
	//// ƽ������
	//printf("audio bitrate %lld kb/s\n", (int64_t)audiostream->codec->bit_rate / 1000);
	return audio_stream_idx;
}

int MMAVReader::getStreamCount() {
	return readerPrivate->avformatContext->nb_streams;
}

int MMAVReader::getStream(MMAVStream* mmavStream, int index) {
	AVStream *ffmpgeStream = readerPrivate->avformatContext->streams[index];    
	mmavStream->streamIndex = ffmpgeStream->index;
	mmavStream->setTimeBase(ffmpgeStream->time_base.den, ffmpgeStream->time_base.num);
	// ��������
	return avcodec_parameters_copy(mmavStream->streamPrivate->codecParamet, ffmpgeStream->codecpar);
}


int MMAVReader::close() {
	if (readerPrivate->avformatContext == nullptr) {
		return -1;
	}
	avformat_close_input(&readerPrivate->avformatContext);
	return 0;
}

int MMAVReader::read(MMAVPacket* mmavavpacket) {
	if (readerPrivate->avformatContext == nullptr) {
		return -1;
	}
	
	int ret = av_read_frame(readerPrivate->avformatContext, mmavavpacket->avpacketPrivate->avpacket);

	return ret;
}

