#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


#define EN_485 4

int main(void)
{
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }
    pinMode(EN_485, OUTPUT);
    digitalWrite(EN_485,HIGH);

    int fd;
    if((fd = serialOpen ("/dev/ttyS0",9600)) < 0) {
        printf("serial err\n");
        return -1;
    }

    int i = 0;
    for (i = 0; i < 100; i++)
    {
        serialPuts(fd, "010600010300D8FA\r\n");

        sleep(1);
    }

    serialClose(fd);
    return 0;
}
