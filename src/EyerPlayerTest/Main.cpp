#include "EyerCore/EyerCore.hpp"

#include "EyerPlayer/EyerPlayer.hpp"

int main()
{
    Eyer::EyerPlayer player;
    player.SetURL("https://www.zzsin.com/hdr/V/ysjf.m3u8");

    player.Play();

    Eyer::EyerTime::EyerSleepMilliseconds(15 * 1000);

    player.Stop();
    return 0;
}