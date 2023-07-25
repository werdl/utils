#ifndef _XTRA_VEC
#include "../xtra.h"
#endif
void fail(char * msg, char * test);
void succ(char * test);


int rett1() {
    ret1;
}
int TestLogic() {
    bool failed=false;
    
    if ((1 and 1)!=(1 && 1)) fail("and!=&&","TestLogic"),failed=true;
    if ((1 or 1)!=(1 || 1)) fail("or!=||","TestLogic"),failed=true;
    if ((nor(1,1))!=(!(1 or 1))) fail("nor(a,b)!=!(a,b)","TestLogic"),failed=true;

    if (rett1()!=1) fail("ret1!=return 1","TestLogic"),failed=true;

    if ((1==1)!=(1 is 1)) fail("is!=(==)","TestLogic"),failed=true;

    if (!failed) succ("TestLogic");
}