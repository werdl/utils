#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <sys/wait.h>
#include <unistd.h>
#include "nlohmann/json"
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>

using json=nlohmann::json;

#define DIGI_VERSION "0.1"

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
    "newthing",
    "create"
};
std::string current="";
#define NumCmds 2
int CmdCd(char ** args) {
    if (args[1]==NULL) error("Insufficient args error for \"cd\"");
    else {
        if (chdir(args[1])!=0) error("Failed to change directory");
    }
    return 1;
}
json jnewthing(std::string name, std::string desc, std::string time) {
    json thing;
    thing["name"]=name;
    thing["desc"]=desc;
    thing["time"]=time;
    std::cout << thing.dump(4);
    return thing;
}
int create(char ** args) {
    std::ofstream fp;
    fp.open((strcat(args[1],".digi.json")));
    json digi,desc;
    desc["name"]=args[1];
    desc["timestamp"]=(int)time(NULL);
    desc["digi_v"]=DIGI_VERSION;

    digi["desc"]=desc;

    digi["things"]={};

    fp << digi.dump(4);

    fp.close();
    current=(strcat(args[1],".digi.json"));
}
int newthing(char ** args) {
    std::string endres;
    std::fstream f;
	f.open(current, std::ios::in);
    char ch;

    while (1) {
        f >> ch;
        if (f.eof())
            break;
        endres+=ch;
    }

    json digi=json::parse(endres);

    digi["things"]+=jnewthing(args[1],args[2],args[3]);
	
    f << digi.dump(4);
    f.close();
}
int (*CmdFunctions[])(char **) = {
    &create,
    &newthing
};
int execute(char ** args) {
    if (args[0]==NULL) return 1;
    for (int i=0;i<NumCmds;i++) {
        std::cout << cmds[i];
        if (!strcmp(args[0],cmds[i]))  {
            printf("\n");
            return (*CmdFunctions[i])(args);
        }
    }
    return 0;
}

int main(int argc, char ** argv) {
    while (1) {
        execute(SplitLine(ReadLine()));
    }
}