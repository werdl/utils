#include <cstdio>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
void strrep(char * s, const char * find, const char * rep){
    if (strstr(s, find)!=NULL){
        char * tmp = (char *)malloc(strlen(strstr(s, find) + strlen(find)) + 1);
        strcpy(tmp, strstr(s, find) + strlen(find));
        *strstr(s, find) = '\0';
        strcat(s, rep);
        strcat(s, tmp);
        free(tmp);
    }
}
#define error(s) ErrorProper(s,__FUNCTION__)
class wsh {
    public:
        int INIT_BUF=1024;
        char * delimiters=" \t\r\n";
        int TOK_BUF=128;
    private:
        char ** CurrentTokens;
        char * CurrentLine;
    public:
        void SplitLine(void) {
            int BufferSize=this->TOK_BUF;
            int pos=0;
            this->CurrentTokens=(char **)malloc(sizeof(char *)*BufferSize);
            if (!this->CurrentTokens) error("Allocation error");

            this->CurrentTokens=strtok(line,DELIMS);
            while (this->CurrentTokens!=NULL) {
                this->CurrentTokens[pos]=token;
                ++pos;
                if (pos>=BufferSize) {
                    BufferSize+=TOK_BUF;
                    this->CurrentTokens=realloc(this->CurrentTokens,sizeof(char *)*BufferSize);
                    if (!this->CurrentTokens) error("Allocation error");
                }
                token=strtok(NULL,DELIMS);
            }
        }
};