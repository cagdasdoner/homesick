#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "camera.h"

#define CAM_FILE "cam.jpg"

pthread_t tid;

void* CAMThread()
{
    char system_cmd[MAX_SYSTEM_CMD_LEN];
    memset(system_cmd, 0, MAX_SYSTEM_CMD_LEN);
    sprintf(system_cmd, "raspistill -o %s", CAM_FILE);
	system(system_cmd);

	if( access( CAM_FILE, F_OK ) != -1 )
	{
    	printf("\nFile found, mailing...\n");
        memset(system_cmd, 0, MAX_SYSTEM_CMD_LEN);
        sprintf(system_cmd, "mpack -s \"Captured\" %s %s", CAM_FILE, EMAIL_TO_POST);
    	system(system_cmd);
    	printf("\nMail sent.\n");
        memset(system_cmd, 0, MAX_SYSTEM_CMD_LEN);
        sprintf(system_cmd, "rm -rf %s", CAM_FILE);
    	system(system_cmd);
    	printf("Cleared. OK.\n");
	}
	else
	{
		printf("File NOT found!!!!!!\n");
	}
    pthread_cancel(tid);
	printf("\nThread was deleted successfully.\n");
    
    return NULL;
}

void CAMShot()
{
    int err = pthread_create(&tid, NULL, &CAMThread, NULL);
    if (err != 0)
    {
        printf("Can't create thread :[%s]", strerror(err));
    }
    else
    {
        printf("Thread created successfully\n");
    }
}
