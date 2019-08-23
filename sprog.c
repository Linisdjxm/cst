#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "func.h"
#include "sprog.h"
#include "equation.h"
_Noreturn void fact_main(int x)
{
    int a = x;
    int * temp = malloc(sizeof(int));
    *temp = printf("%lld\n",fact(a));
    free(temp);
    exit(EXIT_SUCCESS);
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
    exit(EXIT_SUCCESS);

}
_Noreturn void r_amd_b_main(void)
{
    int red[6];
    ranari(red,5,33,1,0);
    int blue = rand()%16+1;
    printf("Wait......\n");
    sleep(1);
    cls();
    printf("RED:");
    print_num(red,6,0,1);
    printf("\nBLUE:%d\n",blue);
    sleep(3);
    cls();
    int count = 1;
    while(1)
    {
        int red[6];
        ranari(red,5,33,1,0);
        int blue = rand()%16+1;

        int rred[6];
        ranari(rred,5,33,1,0);
        int rblue = rand()%16+1;

        printf("It's %d times.\nRRED:",count);
        print_num(rred,6,0,1);
        printf("\nRBLUE:%d\n\n",rblue);
        printf("RED:");
        print_num(red,6,0,1);
        printf("\nBLUE:%d\n",blue);
        if(ats1i(red,rred,6) == 0&&blue == rblue)
        {
            cls();
            printf("%d times!（FIRST）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if(ats1i(red,rred,6) == 0)
        {
            cls();
            printf("%d times!（SECOND）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if(ats1i(red,rred,6) == 0)
        {
            cls();
            printf("%d times!（SECOND）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if(ats1i2(red,rred,6) == 1&&blue == rblue)
        {
            cls();
            printf("%d times!（THIRD）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if((ats1i2(red,rred,6) == 1) || ((ats1i2(red,rred,6) == 2)&&blue == rblue))
        {
            cls();
            printf("%d times!（FOURTH）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if((ats1i2(red,rred,6) == 2) || ((ats1i2(red,rred,6) == 3)&&blue == rblue))
        {
            cls();
            printf("%d times!（FIFTH）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        if(blue == rblue)
        {
            cls();
            printf("%d times!（SIXTH）\n",count);
            printf("It's %d times.\nRRED:",count);
            print_num(rred,6,0,1);
            printf("\nRBLUE:%d\n\n",rblue);
            printf("RED:");
            print_num(red,6,0,1);
            printf("\nBLUE:%d\n",blue);
            break;
        }
        count++;
    }
    exit(0);
}

_Noreturn void stack_main(void)
{
    struct stack *a,*b;
    a = malloc(sizeof(struct stack));
    a->top = 0;
    b = malloc(sizeof(struct stack));
    b->top = 0;
    char input[256];
    scanf("%255s",input);
    getchar();
    int count = 0;
    int len = (int)strlen(input);
    while(1)
    {
        if(input[count] == '(' || input[count] == '[' || input[count] == '{')
            s_push(a,input[count]);
        if(input[count] == ')' || input[count] == ']' || input[count] == '}')
            s_push(b,input[count]);
        count++;
        if(count == len)
            break;
    }
    if(s_qtop(a) != s_qtop(b))
        puts("NO!");
    else {
        puts("YES!");
    }
    free(a);
    free(b);
    exit(EXIT_SUCCESS);
}

_Noreturn void xr_main(void)
{
    int a;
    scanf("%d",&a);
    getchar();
    int x[a];
    int count = 0;
    while(1)
    {
        int temp;
        scanf("%d",&temp);
        x[count] = temp;
        count++;
        if(count == a)
            break;
    }
    int temp2;
    count = 0;
    int uu = 0;
    while(1)
    {
        int count2 = 0;
        temp2 = x[count];
        while(1)
        {
            if(temp2 == x[count2]&&count != count2)
            {
                x[count2] = -1;
                uu++;
            }
            count2 ++;
            if(count2 == a + 2)
                break;
        }
        count++;
        if(count == a + 2)
            break;
    }
    printf("%d\n",a - uu + 2);
    bsort(x,a);
    int *tx = x + (uu - 2);
    print_num(tx,a-uu + 2,1,1);
    exit(EXIT_SUCCESS);
}

int ma_main(void)
{
#define S_MAX 10000
    bool all[S_MAX];
    int count = 0;
    while(1)
    {
        all[count] = true;
        count++;
        if(count == S_MAX)
            break;
    }
    count = 0;
    while(1)
    {
        if(count % 2 == 0&&count != 0 &&count != 2)
            all[count] = false;
        count++;
        if(count == S_MAX)
            break;
    }
    count = 2;
    int o1c = 0;
    int o2c = 0;
    while(1)
    {
        while(1)
        {
            count++;
            if(count>=S_MAX||all[count]==true)
                break;
        }
        if(count >= S_MAX)
            break;
        while(1)
        {
            if(o1c % count == 0&&o1c != 0 &&o1c != count)
                all[o1c] = false;
            o1c++;
            if(o1c == S_MAX)
                break;
        }
        o1c = 0;
    }
    int f = 0,s = 0;
    while(1)
    {
        if(all[o2c]== true)
        {
            printf("%d ",o2c);
            if(o2c >= 80000&&o2c < 90000)
                f++;
            else if(o2c >= 70000&&o2c<80000)
                s++;
        }
        o2c++;
        if(o2c == S_MAX)
            break;
    }
    printf("\n\n%d,%d\n",f,s);
    puts("");
    return 0;
}

