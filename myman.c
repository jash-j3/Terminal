#include"Headers.h"

void cdman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/cd.txt" , mymannew);
    FILE* file = fopen(addressman , "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void lsman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/myls.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void cpman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/mycp.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void mvman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/mymv.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void exitman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/exit.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void grepman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/mygrep.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void psman(char * mymannew)
{
    char addressman[MAX + 25];
    memset(addressman , '\0' , MAX + 25);
    sprintf(addressman , "%s/man/myps.txt" , mymannew);
    FILE* file = fopen(addressman, "r");
    char line[1000];
    memset(line , '\0' , 1000);
    while(fgets(line , 1000 ,file))
    {
        printf("%s" , line);
        memset(line , '\0' , 1000);
    }
    fclose(file);
}

void man(int args , char parsedInput[MAX][MAX] , char* mymannew)
{
    if(args == 0)
    {
        lsman(mymannew);
        cpman(mymannew);
        mvman(mymannew);
        exitman(mymannew);
        psman(mymannew);
        grepman(mymannew);
        cdman(mymannew);
    }
    else if(!strcmp(parsedInput[2] , "cd")) cdman(mymannew);
    else if(!strcmp(parsedInput[2] , "myls")) lsman(mymannew);
    else if(!strcmp(parsedInput[2] , "mycp")) cpman(mymannew); 
    else if(!strcmp(parsedInput[2] , "mymv")) mvman(mymannew);
    else if(!strcmp(parsedInput[2] , "exit")) exitman(mymannew);
    else if(!strcmp(parsedInput[2] , "myps")) psman(mymannew);
    else if(!strcmp(parsedInput[2] , "mygrep")) grepman(mymannew);
    else 
    {
        printf("Type a valid command!!!!!\n");
    }
}
    