#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define unused __attribute__((__unused__))
#if __STDC_VERSION__ >= 199901L
#define __FUNCTION__ __func__
#else
#define __FUNCTION__ "Unknown"
#endif
#define INIT_BUF 1024
#define DELIMS " \t\r\n"
#define TOK_BUF 128
void ErrorProper(char * s,const char * funcname) {
    printf("%s::%d@%s - %s",__FILE__,__LINE__,funcname,s);
    exit(EXIT_FAILURE);
}
#define error(s) ErrorProper(s,__FUNCTION__)
void strrep(char * s, const char * find, const char * rep){
    if (strstr(s, find)!=NULL){
        char * tmp = malloc(strlen(strstr(s, find) + strlen(find)) + 1);
        strcpy(tmp, strstr(s, find) + strlen(find));
        *strstr(s, find) = '\0';
        strcat(s, rep);
        strcat(s, tmp);
        free(tmp);
    }
}
char * ReadLine(void) {
    char * line=NULL;
    size_t bs=0;
    char * buf=malloc(INIT_BUF);
    char * strbuf=malloc(INIT_BUF);
    char * usrbuf=malloc(INIT_BUF);
    char * hostbuf=malloc(INIT_BUF);
    gethostname(hostbuf, sizeof(hostbuf));
    strcpy(strbuf,"/home/");
    getcwd(buf,INIT_BUF);  
    getlogin_r(usrbuf,INIT_BUF);
    strcat(strbuf,usrbuf);
    if (!strncmp(buf,strbuf,strlen(strbuf))) {
        strrep(buf,strbuf,"~");
    }
    printf("%s@%s [%s] %s ",usrbuf,hostbuf,buf,(!strcmp(usrbuf,"root"))?"#":"$");
    if (getline(&line, &bs, stdin)==-1) error("EOF entered");
    return line;
}
char ** SplitLine(char * line) {
    int BufferSize=TOK_BUF,pos=0;
    char ** tokens=malloc(sizeof(char *)*BufferSize);
    char * token;
    if (!tokens) error("Allocation error");

    token=strtok(line,DELIMS);
    while (token!=NULL) {
        tokens[pos]=token;
        ++pos;
        if (pos>=BufferSize) {
            BufferSize+=TOK_BUF;
            tokens=realloc(tokens,sizeof(char *)*BufferSize);
            if (!tokens) error("Allocation error");
        }
        token=strtok(NULL,DELIMS);
    }
    tokens[pos]=NULL;
    return tokens;
}
int launch(char ** args) {
    pid_t pid;
    unused pid_t wpid;
    int status;
    pid=fork();
    
    if (pid==0) {
        // child
        if (execvp(args[0], args)==-1) error("execvp error");
    } else if (pid<0) {
        error("Fork error");
    } else {
        // parent
        do {
            wpid=waitpid(pid,&status,WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
char * builtins[]={
    "cd","help","exit"
};
#define NumBuiltins (int)(sizeof(builtins)/sizeof(char *))
int BuiltinCd(char ** args) {
    if (args[1]==NULL) error("Insufficient args error for \"cd\"");
    else {
        if (chdir(args[1])!=0) error("Failed to change directory");
    }
    return 1;
}
int BuiltinHelp(unused char ** args) {
    printf("Like a normal shell, but much worse.\n");
    printf("builtins:\n");
    for (int i=0;i<NumBuiltins;i++) printf("\t%s\n",builtins[i]);
    return 1;    
}
int BuiltinExit(unused char ** args) {
    exit(EXIT_SUCCESS);
}
int (*BuiltinFunctions[]) (char **) = {
    &BuiltinCd,
    &BuiltinHelp,
    &BuiltinExit
};
int execute(char ** args) {
    if (args[0]==NULL) return 1;
    for (int i=0;i<NumBuiltins;i++) {
        if (!strcmp(args[0],builtins[i])) return (*BuiltinFunctions[i])(args);
    }
    return launch(args);
}
int main() {
    while (true) {
        execute(SplitLine(ReadLine()));
    }
}