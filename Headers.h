#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h>
#include<time.h>
#define line_size 256
#define MAX 256
#define len 1000
void cd(char*);
int ls( char* dir , char parsedInput[2][MAX] , int args);
void my_cp_mv(char parsedInput[MAX][MAX] , int args);
void myps(char flags[MAX]);
void mygrep(char parsedInput[MAX][MAX] , int args);
void man(int args , char parsedInput[MAX][MAX] , char help[MAX]);
typedef struct process {
    int pid;
    int ppid;
    int sid;
    char cmd[len];
    char cmd_full[len];
    char status;
    unsigned long long  int rss;
    long int sz;
    int uid;
    char username[MAX];
    int psr; 
    char tty_name[MAX];
    long long int utime; 
    long long int stime; 
    long long cuttime;     
    long long int cstime;
    time_t  STIME;
    char formatted_time[MAX];
    char formatted_STIME[MAX];
    int c;
}process;
typedef struct str_sptt {
    char file_name[MAX];
    char dir_name[MAX];
}str_sptt;
void divide(str_sptt* path , char * name );
#define cyan "\001\e[01;36m\002"
#define red "\001\e[01;31m\002"
#define rmcolor "\001\e[0m\002 "
#define rm "\001\e[0m\002"
#define yellow "\001\e[00;33m\002"
#define green "\033[1;32m"
#define blue "\001\e[01;34m\002" 
#define white "\033[0m" 