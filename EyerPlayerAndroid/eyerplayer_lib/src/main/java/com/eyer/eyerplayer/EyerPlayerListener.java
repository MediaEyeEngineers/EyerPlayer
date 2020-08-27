package com.eyer.eyerplayer;

import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

public interface EyerPlayerListener {

    public static final int OPEN_STATUS_SUCCESS = 0;
    public static final int OPEN_STATUS_FAIL = -1;
    public static final int OPEN_STATUS_BUSY = -2;

    public int onOpen           (int status, EyerMediaInfo mediaInfo);
    public int onProgress       (double progress);
}
