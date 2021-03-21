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
	
	long tduration = readerPrivate->avformatContext->duration;         //这里获取的是微秒，需要转成秒
	     

	printf("视频时长为%d秒\n", tduration / 1000000);
	

	if (ret==0) {
		av_seek_frame(readerPrivate->avformatContext, -1, startTimePlay* AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
		avformat_find_stream_info(readerPrivate->avformatContext, nullptr);
	}

	return ret;
}

int MMAVReader::getVideo() {
	int video_stream_idx = av_find_best_stream(readerPrivate->avformatContext, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
	long tduration = readerPrivate->avformatContext->streams[video_stream_idx]->duration;
	//// 该码流的总帧数
	//printf("video nb_frames: %lld\n", readerPrivate->avformatContext->streams[video_stream_idx]->nb_frames);
	//// 编码类型
	//printf("video codec_id: %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->codec_id);
	//printf("video codec_name: %s\n", avcodec_get_name(readerPrivate->avformatContext->streams[video_stream_idx]->codec->codec_id));
	//// 图像的宽高尺寸，码流中不一定存在该信息，会由解码后覆盖
	//printf("video width x height: %d x %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->width, readerPrivate->avformatContext->streams[video_stream_idx]->codec->height);
	//// 原始图像的格式，码流中不一定存在该信息，会由解码后覆盖
	//printf("video pix_fmt: %d\n", readerPrivate->avformatContext->streams[video_stream_idx]->codec->pix_fmt);
	//// 总码率
	//printf("video bitrate %lld kb/s\n", (int64_t)readerPrivate->avformatContext->streams[video_stream_idx]->codec->bit_rate / 1000);
	//// 平均码率
	//printf("video avg_frame_rate: %d fps\n", readerPrivate->avformatContext->streams[video_stream_idx]->avg_frame_rate.num / readerPrivate->avformatContext->streams[video_stream_idx]->avg_frame_rate.den);

	return video_stream_idx;
}

int MMAVReader::getAudio() {
	int audio_stream_idx = av_find_best_stream(readerPrivate->avformatContext, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
	AVStream* audiostream = readerPrivate->avformatContext->streams[audio_stream_idx];
	//// 编码类型
	//printf("audio codec_id: %d\n", audiostream->codec->codec_id);
	//printf("audio codec_name: %s\n", avcodec_get_name(audiostream->codec->codec_id));
	//// 音频的采样率
	//printf("audio sample_rate: %d\n", audiostream->codec->sample_rate);
	//// 音频的通道数
	//printf("audio channels: %d\n", audiostream->codec->channels);
	//// 音频的格式，位宽
	//printf("audio sample_fmt: %d\n", audiostream->codec->sample_fmt);
	//// 每个音频帧的 sample 个数
	//printf("audio frame_size: %d\n", audiostream->codec->frame_size);
	//// 该码流的总帧数
	//printf("audio nb_frames: %lld\n", audiostream->nb_frames);
	//// 平均码率
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
	// 拷贝参数
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

