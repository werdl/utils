#include "xtra.h"



int main() {
    XtraVector2D * test=NewXtraVector2D(3,3);
    XtraVector2DNewRow(&test);
    XtraVector2DNewRow(&test);
    XtraVector2DPush(&test,(void *)2,1);
    void * res=XtraVector2DGrab(&test,1,0);
    printf("%p",res);
    XtraVector2DSet(&test,4,1,0);
    printf("%p",XtraVector2DGrab(&test,1,0));
}
// XtraVectorIndex((XtraVector **)&(test->data[1]),0))