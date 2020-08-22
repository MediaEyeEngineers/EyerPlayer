package com.eyer.eyerplayer.mediainfo;

public class EyerMediaInfo {

    private EyerVideoStreamInfo videoStreamInfo = null;

    public EyerMediaInfo(){
        videoStreamInfo = new EyerVideoStreamInfo();
    }

    public int setVideoStreamInfo(int width, int height){
        videoStreamInfo.setWidth(width);
        videoStreamInfo.setHeight(height);

        return 0;
    }

    public EyerVideoStreamInfo getVideoStreamInfo() {
        return videoStreamInfo;
    }

    public void setVideoStreamInfo(EyerVideoStreamInfo videoStreamInfo) {
        this.videoStreamInfo = videoStreamInfo;
    }
}
