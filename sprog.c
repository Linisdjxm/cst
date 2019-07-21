#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"
#include "sprog.h"
#include "equation.h"
_Noreturn void fact_main(int x)
{
    int a = x;
    int * temp = malloc(sizeof(int));
    *temp = printf("%lld\n",fact(a));
    free(temp);
}
_Noreturn void equ_main(void)
{
    while(1){
        double a,b,c,x;
        char sym,frac_i;
        printf("Do you want to input fraction?[Y/N]");
        frac_i = (char)getchar();
        getchar();
        if(frac_i == 'Y')
        {
            frac_mode();
            continue;
        }
        if(frac_i == 'Q')
        {
            exit(0);
        }
        scanf("%lf%*c%c%lf%*c%lf",&a,&sym,&b,&c);
        if((int)a == 0)
        {
            printf("EXIT FAILURE\n");
            exit(EXIT_FAILURE);
        }
        if(sym == '+')
        {
            x =(c - b)/a;
        }
        else if(sym == '-'){
            x =(c + b)/a;
        }
        else{
            printf("EXIT FAILURE\n");
            exit(EXIT_FAILURE);
        }
        printf("x=%f\n",x);
        getchar();
        getchar();
        system("clear");
    }
}

_Noreturn void udlr_main(void)
{
    while (1) {
    char input[10];
    int count = 0;
    while(1)
    {
        input[count] = (char)getch();
        if(count == 2)
            break;
        count++;
    }
    if(input[2] == 'A')
    {
        printf("UP\n");
    }
    if(input[2] == 'B')
    {
        printf("DOWN\n");
    }
    if(input[2] == 'C')
    {
        printf("RIGHT\n");
    }
    if(input[2] == 'D')
    {
        printf("LEFT\n");
    }
    }
}
_Noreturn void game1_main(void)
{
    putchar('#');
    int h_count = 0;
    int l_count = 0;
    while(1){
        int choose = fxpd();
        if(choose == 1)
        {
            if(h_count <= 0)
                continue;
            cls();

            h_count--;
            WHAT_DOSE_THIS_FUNC_REALLY_DO_('\n',h_count);
            WHAT_DOSE_THIS_FUNC_REALLY_DO_(' ',l_count);
            putchar('#');
        }
        else if(choose == 2)
        {
            cls();
            h_count++;
            WHAT_DOSE_THIS_FUNC_REALLY_DO_('\n',h_count);
            WHAT_DOSE_THIS_FUNC_REALLY_DO_(' ',l_count);
            putchar('#');
        }
        else if(choose == 3)
        {
            if(l_count <= 0)
                continue;
            cls();

            l_count--;
            WHAT_DOSE_THIS_FUNC_REALLY_DO_('\n',h_count);
            WHAT_DOSE_THIS_FUNC_REALLY_DO_(' ',l_count);
            putchar('#');
        }
        else if(choose == 4)
        {
            cls();
            l_count++;
            WHAT_DOSE_THIS_FUNC_REALLY_DO_('\n',h_count);
            WHAT_DOSE_THIS_FUNC_REALLY_DO_(' ',l_count);
            putchar('#');
        }
        printf("(%d,%d)",l_count,h_count);
    }
}
_Noreturn void game2_main(void)
{
    int x_lc = 0;
    int y_hc = 0;
    while(1)
    {
        fflush(NULL);
        sleep(1);
        PCTXY('@',x_lc,y_hc,&print_m);
        pzb(x_lc,y_hc);
        x_lc++;
        if(x_lc > 10)
        {
            break;        }
    }
}
