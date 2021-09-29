#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerPlayer/EyerPlayer.hpp"

int main(int argc,char **argv)
{
    printf("hello world\n");

    Eyer::EyerPlayer player;

    player.Start();

    Eyer::EyerTime::EyerSleepMilliseconds(1000 * 10);

    player.Pause();

    player.Stop();


    return 0;
}