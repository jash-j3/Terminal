#include"Headers.h"
int args = 0;
char user[MAX];
char dir[MAX];
char hostname[MAX];
char manadd[MAX];
char prompt[MAX];   
void getAddress(){
    getcwd(dir, MAX);
    getlogin_r(user, MAX);
    gethostname(hostname, MAX);
    strcat(prompt, green);
    strcat(prompt, user);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, white);
    strcat(prompt, ":");
    strcat(prompt, blue);
    strcat(prompt, dir);
    strcat(prompt, white);
    strcat(prompt, "$");
    strcat(prompt, rmcolor);
}
char* lsp(char* input){
    char *modInput = (char *)malloc(MAX * sizeof(char)); bool spce = 0; int x = 0;
    for (int i = 0; i < MAX; i++){
        if (input[i] != ' ' && !spce){
            spce = 1;
            modInput[x] = input[i];
            x++;
        }
        else if (spce){
            modInput[x] = input[i];
            x++;
        }
    }
    return modInput;
}
void Parse(char * input , char parsedInput[MAX][MAX]){
    int z =0;
    bool y =0,cmd =1;
    int flags = 0;
    for(int i = 0 ; i < strlen(input); i++)
    {
        if(cmd && input[i]!= ' ')
        {
            parsedInput[0][z] = input[i];
            z++;
        }
        else if(input[i] == ' ')
        {
            cmd = 0;
            y =1;
            z = 0;
        }
        else if(y == 1 && input[i] == '-')
        {
            i++;
            while(input[i]!=' ' && i < strlen(input))
            {
                parsedInput[1][flags] = input[i];
                flags++;
                i++;
            }
        }
        else if(y == 1 && input[i] != '-')
        {
            while(input[i]!= ' ' && i < strlen(input))
            {
                parsedInput[args+2][z] = input[i];
                i++;
                z++;
            }
            parsedInput[args+2][z] = '\0';
            z=0;
            args++;
        }
    }
    lsp(parsedInput[0]);
}
int main(){
    memset(manadd , '\0' , MAX);
    getcwd(manadd , MAX);
    while(1){
        prompt[0] = '\0';
        getAddress();
        args = 0;
        char parsedInput[MAX][MAX];
        char input[MAX];
        for(int i = 0 ; i< MAX ;i++)
        {
            input[i] = '\0';
            for(int j = 0 ; j<MAX ;j++)
            {
                parsedInput[i][j] = '\0';
            }
            
        }
        strcpy(input , readline(prompt));
        strcpy(input , lsp(input));
        Parse(input , parsedInput);
        getcwd(parsedInput[args+2] , MAX);
        if(strlen(input) != 0) add_history(input);
        if(!strcmp(parsedInput[0] , "cd"))
        {
            if(input[2] == ' ') cd(input);
            else printf("Invalid command\n");
        }
        else if(!strcmp(parsedInput[0], "exit")) 
        {
            if(args> 0 || parsedInput[1][0] != '\0')
            {
                printf("Invalid syntax \nPlease check man exit\n");
                continue;
            }
            break;
        }
        else if(!strcmp(parsedInput[0] , "myls") ) 
        {
            ls(dir , parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "mycp") || !strcmp(parsedInput[0] , "mymv"))
        {
            my_cp_mv(parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "myps"))
        {
            if(args!= 0)
            {
                printf("Invalid Syntax for ps\nPlease check man\n");
                continue;
            }
            myps(parsedInput[1]);
        }
        else if(!strcmp(parsedInput[0] , "mygrep"))
        {
            mygrep(parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "myman"))
        {
            if(parsedInput[1][0] != '\0')
            {
                printf("Invalid. Pleade try man with command name\n");
                continue;
            }
            else if(args > 1)
            {
                printf("Invalid. Pleade try man with command name\n");
                continue;
            }

            man(args , parsedInput , manadd);
        }
        else printf("Invalid\n");
    }
    return 0;
}