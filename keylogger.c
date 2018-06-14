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

int main(int argc, char *argv[]) {
    struct input_event input_ev;

    return 0;
}
