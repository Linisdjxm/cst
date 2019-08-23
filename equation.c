#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "equation.h"

void frac_mode(void)
{
    puts("ax+b = c or ax-b = c\n");
    struct frac a,b,c,x,t;
    input_frac(&a,'a');
    input_frac(&b,'b');
    input_frac(&c,'c');
    char sym;
    printf("Do you want \"ax");
    cputchar(I_RED,B_BLACK,'+');
    printf("b=c\" or \"ax");
    cputchar(I_RED,B_BLACK,'-');
    printf("b = c\"?[+/-]") ;
    sym = (char)getchar();
    getchar();

    if(sym == '+')
    {
        sub_frac(c,b,&t);
        div_frac(t,a,&x);
        put_frac(x);
    }
    else
    {
        plus_frac(b,c,&t);
        div_frac(t,a,&x);
        put_frac(x);
    }
    printf("\n");
    getchar();
    system("clear");
}
