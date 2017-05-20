#include "mqtt.h"
#include "network.h"
#include "global.h"

int main(int argc, char* argv[])
{
    NETBegin();
    MQTTBegin();

    MQTTSubscribe(CAMERA_TOPIC);

    printf("\nPress Q<Enter> to quit.\n\n");
    int ch;
    do 
    {
        ch = getchar();
    }while(ch!='Q' && ch != 'q');

    MQTTDisconnect();

    return 0;
}
