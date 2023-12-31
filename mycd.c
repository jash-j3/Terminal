#include"Headers.h"
char  newDir[MAX];
char* ck(char* input){
    int leng = strlen(input);
    char *inp = (char *)malloc(MAX * sizeof(char));
    if ((input[0] == '\'' && input[leng - 1] == '\'') ||(input[0] == '\"' && input[leng - 1] == '\"')) {
        for (int i = 0; i < leng - 2; i++) inp[i] = input[i + 1];
        inp[leng - 2] = '\0';
        return inp;
    }
    else return input;
} 
void cd(char* input){
    for (int i = 0; i < 97; i++) newDir[i] = input[i + 3];
    strcpy(newDir, ck(newDir));
    if(chdir(newDir) == -1)
    printf("Invalid Directory\n");
}