#pragma once

class MMAVStream;
class MMAVStreamPrivate;
class MMAVPacketPrivate;
class MMAVFreamPrivate;
class MMAVReaderPrivate;
class MMAVDecoderPrivate;



class MMAVTime {
public:
	static long long getTime();
};


class MMAVPacket {
public:
	MMAVPacket();
	~MMAVPacket();
	int getStreamIndex();
public :
	MMAVPacketPrivate* avpacketPrivate = 0;
};



class MMAVFream {
public:
	MMAVFream();
	~MMAVFream();
	void PrintFream();

	long long getFreamTime();

	void setData(int* w, int* h, int* c);
	unsigned char* getYUVData(int i);
	// unsigned char* toRGB();

public:
	MMAVFreamPrivate* avFreamPrivate = 0;
};





class MMAVReader {
public :
	MMAVReader();
	~MMAVReader();

public:
	int open(const char *path , int startTimePlay);

	int getStreamCount();
	int getStream(MMAVStream *avStream, int index);

	int getVideo();
	int getAudio();

	int close();
	int read(MMAVPacket *avpacket);



private:
	
	MMAVReaderPrivate* readerPrivate = 0;
};




class MMAVStream {
public:
	MMAVStream();
	~MMAVStream();
	int streamIndex = -1;
	MMAVStreamPrivate *streamPrivate = 0;
	void setTimeBase(int den ,int num);

	void test(int type);

public:
	int timeBaseDen;
	int timeBaseNum;
};




class MMAVDecoder {
public:
	MMAVDecoder();
	~MMAVDecoder();
	int init(MMAVStream *MMAVStream);
	int sendPacket(MMAVPacket *mmavpacket);
	int receiveFream(MMAVFream *mmavFream);
	int close();
	

private:
	
	MMAVDecoderPrivate *decoderImpl = 0;
};
