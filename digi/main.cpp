#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <sys/wait.h>
#include <unistd.h>

int create(char ** args) {
    printf("%s", args[1]);
}
#define error(s) printf("Error - %s",s)
#define INIT_BUF 1024
#define DELIMS " \t\r\n"
#define TOK_BUF 128
char * ReadLine(void) {
    char * line=NULL;
    size_t bs=0;
    if (getline(&line, &bs, stdin)==-1) error("EOF entered");
    return line;
}
char ** SplitLine(char * line) {
    int BufferSize=1024,pos=0;
    char ** tokens=(char **)malloc(sizeof(char *)*BufferSize);
    char * token;
    if (!tokens) error("Allocation error");

    token=strtok(line,DELIMS);
    while (token!=NULL) {
        tokens[pos]=token;
        ++pos;
        if (pos>=BufferSize) {
            BufferSize+=TOK_BUF;
            tokens=(char **)realloc(tokens,sizeof(char *)*BufferSize);
            if (!tokens) error("Allocation error");
        }
        token=strtok(NULL,DELIMS);
    }
    tokens[pos]=NULL;
    return tokens;
}
char * cmds[]={
    "create"
};
#define NumCmds (int)(sizeof(cmds)/sizeof(char *))
int CmdCd(char ** args) {
    if (args[1]==NULL) error("Insufficient args error for \"cd\"");
    else {
        if (chdir(args[1])!=0) error("Failed to change directory");
    }
    return 1;
}
int (*CmdFunctions[])(char **) = {
    &create
};
int execute(char ** args) {
    if (args[0]==NULL) return 1;
    for (int i=0;i<NumCmds;i++) {
        if (!strcmp(args[0],cmds[i])) return (*CmdFunctions[i])(args);
    }
    return 0;
}
int main(int argc, char ** argv) {
    while (1) {
        execute(SplitLine(ReadLine()));
    }
}