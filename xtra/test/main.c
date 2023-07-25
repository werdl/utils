#include "fail.h"
#include <stdbool.h>
#include "2dvector.h"
#include "1dvector.h"
#include "matrix.h"
#include "types.h"
#include "logic.h"
#include "cast.h"
int main() {
    TestVector();
    Test2DVector();
    TestMatrix();
    TestTypes();
    TestLogic();
    TestCast();

    printf("    Tests \033[1;32mPASSED\033[0m: %d %s",succe,succe+failed==succe?"(all)":"");
    printf("\n    Tests \033[1;31mFAILED\033[0m: %d",failed);
    if (succe+failed==succe) return 0;
    else return 1;
}