#include"Headers.h"
char curdir[MAX];
bool I =0, n = 0 , u =0 , v =0;
str_sptt curr,final;
char openc[MAX];
void divide(str_sptt* path , char* name){
    int x = strlen(name);
    for(int i = x- 1; i>= 0 ;i--)    {
        if(name[i] == '/'){
            x = i;
            break;
        }
        else if(i == 0) x=-1;
    }
    int o = 0 , p = 0;
    for(int i= 0 ; i < strlen(name) ;i++)
    {
        if(i<=x)
        {
            path->dir_name[o] = name[i];
            path->dir_name[o+1] = '\0';
            o++;
        }
        else
        {
            path->file_name[p] = name[i];
            path->file_name[p+1] = '\0';
            p++;
        }
    }
}
int isThere(char  destination_name[MAX] , char file_name1[MAX]){
    DIR* directory;
    directory = opendir(destination_name); 
    struct dirent* f_1 = (struct dirent*)malloc(sizeof(struct dirent));
    while((f_1 = readdir(directory)) != NULL){
        char newest[MAX];
        if(!strcmp(f_1->d_name , file_name1)) return 1;
    }
    free(f_1);
    closedir(directory);
    return 0;
}
bool tck(struct stat a ,struct stat b){
    long long int t_1 = a.st_mtime;
    long long int t_2 = b.st_mtime;
    if(t_1 > t_2) return 0;
    else return 1;
}   
struct stat current_file_stats;
bool flagss(char file_name[MAX]){
    getcwd(openc, MAX);
    bool checker = isThere(openc , file_name);
    if(u && checker){
        struct stat  atDestination;
        stat(file_name , &atDestination);
        bool latest = tck(current_file_stats , atDestination);
        if(latest) {
            chdir(curdir);
            return 0;
        }
    }

    if(I && checker){
        printf("%s already exists at destination. Overwrite?(y/n)" , file_name);
        char c;
        
        scanf("%c" , &c);
        while(getchar()!= '\n');

        if(tolower(c) != 'y') {
            chdir(curdir);
            return 0;
        }
    }
    else if(n && checker){
        chdir(curdir);
        return 0;
    }
    
    strcpy(final.file_name , file_name);
    

    return 1;
}
void my_cp_mv(char parsedInput[MAX][MAX] , int args)
{
    I =0, n = 0 , u =0 , v =0;
    for(int i =0 ; i < strlen(parsedInput[1]) ; i++)
    {
        if(parsedInput[1][i] == 'i' ) {I= 1;n=0;}
        else if(parsedInput[1][i] == 'n') {n =1;I= 0;}
        else if(parsedInput[1][i] == 'u') u =1;
        else if(parsedInput[1][i] == 'v') v = 1;
        else {
            printf("Invalid flag\n");
            return;
        }
    }
    if(args < 2) printf("Invalid syntax for %s\nPlease check help.\n" , parsedInput[0]);
    getcwd(curdir , MAX);
    for(size_t j = 0 ; j < MAX ; j++) {
        openc[j] = '\0';
        curr.file_name[j] = '\0';
        curr.dir_name[j] = '\0';
        final.dir_name[j] = '\0';
        final.file_name[j] = '\0';
    } 
    FILE* new;
    final.dir_name[0] = '\0';
    divide(&final, parsedInput[args+2 -1]);
    for(int i = 2 ;i < args + 1 ; i++)
    {
        divide(&curr, parsedInput[i]);
        long long int mode;
        FILE* this;
        if(strlen(curr.dir_name) == 0) this = fopen(curr.file_name , "rb");
        else if(chdir(curr.dir_name) != -1) this = fopen(curr.file_name , "rb");
        else 
        {
            printf("%s is Invalid Path for %s\n" , curr.dir_name , curr.file_name);
            continue;
        }
        chdir(curdir);
        if(this == NULL)
        {
            printf("Invalid Source File %s\n" , curr.file_name);
            continue;
        }
        stat(curr.file_name , &current_file_stats);
        mode = current_file_stats.st_mode;
        if(chdir(parsedInput[args + 2 -1]) != -1)
        {
            if(!flagss(curr.file_name)) continue;
            new = fopen(curr.file_name,"wb");
        }
        else if(chdir(final.dir_name) != -1)
        {    
            if(args > 2)
            {
                printf("Invalid Destination Directory\n");
                chdir(curdir);
                break;
            }
            else  
            {
                if(!flagss(final.file_name)) continue;
                new = fopen(final.file_name,"wb");
            }
            
        }
        else
        {
            if(final.dir_name[0] == '\0')
            {
                if(args>2)
                {
                    printf("Invalid Destination Directory\n");
                    chdir(curdir);
                    break;
                }
                else
                {
                    if(!flagss(final.file_name)) continue;
                    new = fopen(final.file_name,"wb");
                    strcpy(curr.dir_name , curdir);
                }
            }
            else
            {
                printf("Destination Directory DNE\n");
                chdir(curdir);
                break;
            }
        }
        chmod(final.file_name , mode);
        char chunks[1];
        while(fread(chunks, 1 ,1, this) == 1) fwrite(chunks, 1 ,1 ,new);
        getcwd(final.dir_name , MAX);
        chdir(curdir);
        chdir(curr.dir_name);
        getcwd(curr.dir_name, MAX);
        if(!strcmp(parsedInput[0], "mymv")) 
        {
            remove(curr.file_name);
            if(v)
            printf("renamed ");
        }
        if(v) printf("\'%s/%s\' -> \'%s/%s\'\n" , curr.dir_name , curr.file_name , final.dir_name, final.file_name);
        fclose(this);
        fclose(new);
        chdir(curdir);
    }
}

