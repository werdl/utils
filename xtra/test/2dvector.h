#include "../xtra.h"
void fail(char * msg, char * test);
void succ(char * test);

int Test2DVector() {
    bool failed=false;
    XtraVector2D * test=NewXtraVector2D(3,3);
    if (XtraVector2DNewRow(&test)) fail("Invalid new row","Test2DVector"), failed=true;
    if (XtraVector2DNewRow(&test)) fail("Invalid new row","Test2DVector"), failed=true;
    if (XtraVector2DPush(&test,(void *)2,1)) fail("Failed Push","Test2DVector"), failed=true;
    void * res=XtraVector2DGrab(&test,1,0);
    if (res!=(void *)2 and res!=(void *)0x2) fail("Failed Grab, wrong value","Test2DVector"), failed=true;
    XtraVector2DSet(&test,(void *)4,1,0);
    res=XtraVector2DGrab(&test,1,0);
    if (res!=(void *)4 and res!=(void *)0x4) fail("Failed Grab, wrong value","Test2DVector"), failed=true;
    if (!failed) succ("Test2DVector");
}