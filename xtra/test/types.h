#ifndef _XTRA_VEC
#include "../xtra.h"
#endif
void fail(char * msg, char * test);
void succ(char * test);

int TestTypes() {
    bool failed=false;
    char buf[32];
    snprintf(buf,33,"%s",GetType(3));
    if (strcmp(buf,"int")) fail("3!=int","TestTypes"),failed=true;

    char buf1[32];
    snprintf(buf1,33,"%s",GetType(3.0));
    if (strcmp(buf1,"double") and strcmp(buf1, "float")) fail("3!=double||float","TestTypes"),failed=true;

    snprintf(buf1,33,"%s",GetType((void *)3));
    if (strcmp(buf1,"void *")) fail("(void *)3!=void *","TestTypes"),failed=true;

    snprintf(buf1,33,"%s",GetType((unsigned long long *)3));
    if (strcmp(buf1,"unsigned long long *")) fail("(unsigned long long *)3!=unsigned long long *","TestTypes"),failed=true;

    snprintf(buf1,33,"%s",GetType(NewXtraVector(3)));
    if (strcmp(buf1,"unknown")) fail("unknown!=XtraVector *","TestTypes"),failed=true;

    if (!failed) succ("TestTypes");
}