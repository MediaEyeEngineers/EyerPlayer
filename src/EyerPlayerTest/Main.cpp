#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerPlayer/EyerPlayer.hpp"

int main(int argc,char **argv)
{
    Eyer::BLOCK_TIME * blockTime = new Eyer::BLOCK_TIME("Main");



    Eyer::EyerPlayer player;
    Eyer::EyerString path = "https://www.zzsin.com/hdr/V/ysjf.m3u8";
    // Eyer::EyerString path = "/Users/miaoyuqiao/Desktop/HDR/ZhongLi.mp4";
    player.SetURL(path);

    player.Play();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 10);

    player.Pause();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 10);

    player.Resume();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 20);

    player.Seek(10.0);
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 20);

    player.Stop();

    delete blockTime;

    return 0;
}
