#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerPlayer/EyerPlayer.hpp"

int main(int argc,char **argv)
{
    Eyer::BLOCK_TIME * blockTime = new Eyer::BLOCK_TIME("Main\n");



    Eyer::EyerPlayer player;

    player.Play();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 10);

    player.Pause();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 1);

    player.Resume();
    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 10);

    player.Stop();

    delete blockTime;

    return 0;
}