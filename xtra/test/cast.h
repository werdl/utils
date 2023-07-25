#ifndef _XTRA_VEC
#include "../xtra.h"
#endif
void fail(char * msg, char * test);
void succ(char * test);



int TestCast() {
    bool failed=false;
    
    if (tbool(2)!=true) fail("bool(2)!=true","TestCast"),failed=true;
    if (tbool("2")!=true) fail("bool(\"2\")!=true","TestCast"),failed=true;



    if (!failed) succ("TestCast");
}