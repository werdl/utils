#include <stdio.h>
int failed=0;
int succe=0;
void fail(char * msg, char * test) {
    fprintf(stdout,"    Test \"%s\" \033[1;31mFAILED\033[0m with error: \"%s\"\n",test,msg);
    ++failed;
}
void succ(char * test) {
    fprintf(stdout,"    Test \"%s\" \033[1;32mPASSED\033[0m\n",test);
    ++succe;
}
