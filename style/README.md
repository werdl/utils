## C-style languages Style Guide
- Personal usage
### Source files
```c
/*  
    Style declaration
    The style I use for all my projects
    For C and C-style languages

    Use American spelling, but British grammar
    
    Always indent this bit
*/

#include <stddef.h> // <> for system headers, "" for your own
#include <stdio.h>
#include <stdlib.h>

#define unused __attribute__((__unused__)) // for marking variables as useless
// Don't forget your space
enum HelloWorld_e { // PascalCase for variable names (and structure suffix)
    HEY_THERE=0, // CAPITAL_SNAKE_CASE for constants
    SO_COOL
};
/*
    Suffixes for structures
    enum - e
    typedef - t
    struct - s
    union - u
*/
// When using functions or structures, { is always on the same line.
// Stick to // unless you have to differ
typedef struct {
    char * data;
    int flags;
} MyStruct_t; // when using typedef, anonymous structs are best.
int MyPascalCaseFunction(void) { // Don't forget to specify!
    const int MyCond=1; // Don't specify which int unless you need to!
    // Going to change? If not, don't forget your const
    int x=!MyCond?42:0; // Tertiary where possible

    return x;
}
char * CheckMyNumber(int number) { // Don't capitalise one word variables
    if (number<=100 || number>=200) return NULL; 
    // Gaps between two conditionals and operator (i.e ||)
    // but not between members of said conditional
    else return "Success :)"; // Use one-liners
}
int main(unused int argc, unused char ** argv) { 
    // Use argc and argv, you'll need them one day
    char line[256];
    int UserInput;
    if (fgets(line, sizeof(line), stdin)) { // fgets for security
        if (sscanf(line, "%d", &UserInput)==1) { // Always check result
            // Use explicit comparisons
            // Nesting is fine, just never forget your indentation!
            if (CheckMyNumber(UserInput)!=NULL) printf("Oof\n"); 
            // one-liners stay on one line, also no commas (just use brackets)
            else {
                printf("yay!\n"); 
                // \n is at the end of one call, not the beginning of the next
                printf("Lucky Number %d\n",UserInput);
            } // if can have no brackets, then the else does
        }
    }
    char * pointer=malloc(256); 
    // space between typename, pointer, and varname
    unused void * AreBetter=NULL; // void * are cool, use them
    switch (UserInput) { // use switch statements
        case 123:
            printf("1,121,12321\n");
            break; // Don't forget to break
        case 456:
            printf("454,455,456,457\n");
            break;
        default: // always a default
            printf("%d is such a boring number\n",UserInput);
            break;
    }
    free(pointer); // memory leaks are not very fun
    for (int i=100;i;i--) printf("i is %d\n",i);
    // Use i,j,k,l,m - you shouldn't need anymore 
    // (you've got bigger problems if you're nesting 6 for loops)
    /*
        while(true) or while(1) is better than
        for(;;)
    */
}
```
### Compilation
```bash
gcc test.c -Wall -Wextra -pedantic -Werror -o test
```
### Things not to use
- C++ like features
- Anything overly complicated
- `goto` and labels unless you REALLY need to
- Let a line go over 79 characters (controversial)
- Change a variable in an expression BUT
> You can change it here
> `buffer[i++]`
> That is ok
- Overuse `if` statement commas
- Overuse `switch`es
- Use `unsigned` when you don't need to.
- Don't write code that feels like it needs a class...
- Or code that really should be C++
