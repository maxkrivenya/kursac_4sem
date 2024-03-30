#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>

int lstat(const char * file, struct stat * buf);
int nanosleep(const struct timespec *requested_time, struct timespec *remaining);
int kill(__pid_t pid, int sig);
int getopt(int argc, char *const *argv, const char *shortopts);

#define PARENT_PATH "./hrun_parent"
#define CONFIG_PATH "./.config"
#define CONTROLLER_PATH "./hrun_controller"
#define HRUN_CHILD "./hrunik"
#define OPT_MASK "lew"
#define LINE_SEPARATOR "\n=============================================\n"

#define MAX_LINE_LENGTH 80

//dd hh mm ss task 
//01 34 67 9  12->
int time_to_proc(char* plan, char* now){
    if(plan==NULL){return -1;}
    if(now==NULL){return -1;}
    for(int i = 0; i < 12; i++){
        if(isdigit(plan[i])){
            if(plan[i]!=now[i]){
                return 0;
            }        
        }
    } 
    return -1;
}

char* get_task_from_string(char* string){
    if(string==NULL){return NULL;}
    int length = strlen(string);
    int shift = 12;
    int i = 0;
    if(length < shift){return NULL;}

    for(i = 0; i < length - shift; i++){
        string[i] = string[i+shift];
    }
    string[i] = '\0';
    return string;
}
