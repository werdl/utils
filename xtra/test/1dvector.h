#ifndef _XTRA_VEC
#include "../xtra.h"
#endif
void fail(char * msg, char * test);
void succ(char * test);

int TestVector() {
    bool failed=false;
    XtraVector * test=NewXtraVector(3);
    if (XtraVectorPush(&test,(void *)2)) fail("Failed Push","TestVector"), failed=true;
    void * res=XtraVectorIndex(&test,0);
    
    if (res!=(void *)2 and res!=(void *)0x2) fail("Failed Grab, wrong value","TestVector"), failed=true;
    test=XtraVectorChangeEl(&test,0,(void *)4);
    res=XtraVectorIndex(&test,0);
    if (res!=(void *)4 and res!=(void *)0x4) fail("Failed Grab, wrong value","TestVector"), failed=true;
    
    
    
    if (!failed) succ("TestVector");
}