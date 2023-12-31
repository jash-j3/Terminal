#include "Headers.h"
long x = 0;                             // to store the sizes
bool l = 0, S = 0, r = 0, a = 0, t = 0; // all the  flags to implement
char time_str[MAX];                     // for the formatted time
struct info{
    char name[MAX];
    struct stat kno;
}; struct info files[1000];
void printPermissions(struct info file); 
void print(struct info file);                 
void time_strings(long long int mod)
{
    time_t rawtime = mod;
    struct tm *info;
    info = localtime(&rawtime);
    strftime(time_str, MAX, "%b %d %H:%M", info);
}
int timeSorting(const void *file1, const void *file2)
{
    long long int x_1 = ((struct info *)file1)->kno.st_mtime;
    long long int x_2 = ((struct info *)file2)->kno.st_mtime;
    return (x_2 - x_1);
}
int namSorting(const void *file1, const void *file2)
{
    char name1[MAX]; strcpy(name1, ((struct info *)file1)->name);
    char name2[MAX]; strcpy(name2, ((struct info *)file2)->name);
    return strcmp(name1, name2);
}
int sizeSorting(const void *file1, const void *file2)
{
    long long int x_1 = ((struct info *)file1)->kno.st_size;
    long long int x_2 = ((struct info *)file2)->kno.st_size;
    return (x_2 - x_1);
}
void L_flag()
{
    if(!r) {
        for (int i = 0; i < x; i++){
            if (a)
                print(files[i]);
            else if (files[i].name[0] != '.')
                print(files[i]);
        }
    }
    else{
        for (int i = x - 1; i >= 0; i--){
            if (a)
                print(files[i]);
            else if (files[i].name[0] != '.')
                print(files[i]);
        }
    }
}
void printPermissions(struct info file)
{
    printf((S_ISDIR(file.kno.st_mode)) ? "d" : "-");
    printf((file.kno.st_mode & S_IRUSR) ? "r" : "-");
    printf((file.kno.st_mode & S_IWUSR) ? "w" : "-");
    printf((file.kno.st_mode & S_IXUSR) ? "x" : "-");
    printf((file.kno.st_mode & S_IRGRP) ? "r" : "-");
    printf((file.kno.st_mode & S_IXGRP) ? "x" : "-");
    printf((file.kno.st_mode & S_IWGRP) ? "w" : "-");
    printf((file.kno.st_mode & S_IROTH) ? "r" : "-");
    printf((file.kno.st_mode & S_IWOTH) ? "w" : "-");
    printf((file.kno.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
}
void print(struct info file)
{
    printPermissions(file);
    struct passwd *pw = (struct passwd *)malloc(sizeof(struct passwd));
    pw = getpwuid(file.kno.st_uid);
    struct group *gr = (struct group *)malloc(sizeof(struct group));
    gr = getgrgid(file.kno.st_gid);
    time_strings(file.kno.st_mtime);
    printf("%4ld %15s %15s ", file.kno.st_nlink, pw->pw_name, gr->gr_name);
    printf("%8ld %16s\t%s \n", file.kno.st_size, time_str, file.name);
}
int ls(char *dir, char parsedInput[MAX][MAX], int args)
{
    l = 0; a = 0; r = 0; S = 0; t = 0;
    char arr[2] = {'\0', '\0'};
    for (size_t i = 0; i < strlen(parsedInput[1]); i++) {
        if (parsedInput[1][i] == 'l') l = 1;
        else if (parsedInput[1][i] == 'a') a = 1;
        else if (parsedInput[1][i] == 'r') r = 1;
        else if (parsedInput[1][i] == 't' || parsedInput[1][i] == 'S') {
            if (parsedInput[1][i] == 'S') S = 1;
            else t = 1;
            arr[0] = parsedInput[1][i];
        }
        else{
            printf("Invalid Command Flag -%c.\nUse help\n", parsedInput[1][i]);
            return 0;
        }
    }
    for (int j = 2; j < (args == 0 ? 3 : args + 2); j++) {
        x = 0;
        long long int ts = 0, hs = 0;
        DIR *directory;
        char newDir[MAX];
        if (args > 0) {
            if (chdir(parsedInput[j]) == -1){
                printf("Invalid Directory\n");
                continue;
            }
            getcwd(newDir, MAX);
            if (args > 1) printf("\n%s:\n", parsedInput[j]);
        }
        else strcpy(newDir, dir);
        directory = opendir(newDir);
        struct dirent *file = (struct dirent *)malloc(sizeof(struct dirent));
        while ((file = readdir(directory)) != NULL)
        {
            stat(file->d_name, &files[x].kno);
            strcpy(files[x].name, file->d_name);
            ts += (files[x].kno.st_blocks);
            if (file->d_name[0] == '.')
                hs += (files[x].kno.st_blocks);
            x++;
        }
        closedir(directory);
        free(file);
        qsort(files, x, sizeof(files[0]), namSorting);
        if (S || t)
        {
            if (arr[0] == 'S')
                qsort(files, x, sizeof(files[0]), sizeSorting);
            else
                qsort(files, x, sizeof(files[0]), timeSorting);
        }
        if (l)
        {
            if (a)
                printf("total %lld\n", ts / 2);
            else
                printf("total %lld\n", (ts - hs) / 2);
            L_flag();
        }
        else
        {
            if (r)
            {
                for (int i = x - 1; i >= 0; i--)
                {
                    if (a == 1)
                        printf("%s\n", files[i].name);
                    else if (files[i].name[0] != '.')
                        printf("%s\n", files[i].name);
                }
            }
            else
            {
                for (int i = 0; i < x; i++)
                {
                    if (a == 1)
                        printf("%s\n", files[i].name);
                    else if (files[i].name[0] != '.')
                        printf("%s\n", files[i].name);
                }
            }
        }
        chdir(dir);
    }
}
