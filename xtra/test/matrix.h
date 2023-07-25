#ifndef _XTRA_VEC
#include "../xtra.h"
#endif
void fail(char * msg, char * test);
void succ(char * test);

int TestMatrix() {
    bool failed=false;
    XtraMatrix * test=NewXtraMatrix(3,3);
    if (XtraMatrixSet(&test,2,2,(void *)2)) fail("Failed Set","TestMatrix"), failed=true;
    void * res=XtraMatrixGrab(&test,2,2);
    
    if (res!=(void *)2 and res!=(void *)0x2) fail("Failed Grab, wrong value","TestMatrix"), failed=true;
    if (XtraMatrixSet(&test,2,2,(void *)4)) fail("Failed Reset, wrong value","TestMatrix"), failed=true;
    res=XtraMatrixGrab(&test,2,2);
    if (res!=(void *)4 and res!=(void *)0x4) fail("Failed Grab, wrong value","TestMatrix"), failed=true;
    if (!failed) succ("TestMatrix");
}