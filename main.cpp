#include <QCoreApplication>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <QThread>

#define EN_485 4

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

        serialFlush(fd);
        serialPrintf(fd,"\r");

//        serialPuts(fd, "12345\n");
//        serialPuts(fd, "56789\n");

        printf("0\r\n");
        QByteArray array;
        array = QByteArray::fromHex("010600010100D99A");
        //serialPuts(fd, array);
        serialPuts(fd, "010600010100D99A");
        printf("1\r\n");
        QThread::sleep(1);
        array = QByteArray::fromHex("010600010200D96A");
        //serialPuts(fd, array);
        serialPuts(fd, "010600010200D96A");
        printf("2\r\n");

        serialFlush(fd);
        serialClose(fd);
        printf("3\r\n");
    }

    return a.exec();
}
