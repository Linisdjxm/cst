#include "func.h"
#include "equation.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <termios.h> //操作终端
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <dirent.h>

void usleep(int micro_seconds);
static volatile sig_atomic_t emnum;
static struct div_s temp;
static bool has_input = false;
void creat_node1(struct node *a,struct node *b);
void creat_node2(struct node *a);

void swap(item a[],int index1,int index2)
{
    item temp_data = a[index2];
    a[index2] = a[index1];
    a[index1] = temp_data;
    return;
}

bool swap_safety(item a[],int size,int index1,int index2)
{
    if(index1 >= size || index2 >= size)
        return false;
    else {
        swap(a,index1,index2);
        return true;
    }
}
void bsort(item a[],int size)
{
#if DEBUG_MODE
    int debug_count = 1;
#endif
    int out_count = 0;
    while(out_count != (size)*(size)){
        int this_index = 0;
        while(this_index < size - 1){
            if(a[this_index] > a[this_index + 1])
                swap(a,this_index,this_index + 1);
            this_index++;
#if DEBUG_MODE
            printf("\nDEBUG        :        %d\n",debug_count);
            print_num(a,size);
            printf("\n\n");
            debug_count++;
#endif
        }
        out_count++;
    }
}
long double abs_l(long double a)
{
    if(a > 0){
        return a;
    }
    else {
        return -a;
    }

}
struct div_s div_l(unsigned long long a,unsigned long long b)
{
    temp.result = a/b;
    temp.remainder = a%b;
    return temp;
}
bool istrb(char *a,int max_index)
{
    int count = 0;
    while(count <= max_index)
    {
        if(isupper(a[count]) == 0){
            return false;}
        count++;
    }
    return true;
}
bool istrs(char *a,int max_index)
{
    int count = 0;
    while(count <= max_index)
    {
        if(islower( a[count]) == 0)
            return false;
        count++;
    }
    return true;
}
void ceprint(int I_color, int B_color, char *mes)
{
    if(I_color == I_WHITE&&B_color ==B_BLACK)
    {
        printf("%s",mes);
        return;
    }
    printf("\033[%dm\033[%dm%s\033[0m",I_color,B_color,mes);
}
void cset(int I_color,int B_color)
{
    printf("\033[%dm\033[%dm",I_color,B_color);
    atexit(recset);
    at_quick_exit(recset);
}
void cputchar(int I_color,int B_color,char meschar)
{
    cset(I_color,B_color);
    putchar(meschar);
    recset();
}
void recset(void)
{
    printf("\033[0m");
}
void input_frac(struct frac *a,int choose)
{
#ifdef EQUATION_IS_ON
    if(!has_input)
    {
        printf("Input a number like +3/5 or -6/7(If you want to input an integer,please input like +7i0(if you want to input +7):)");
        has_input = true;
    }
    else
        printf("Input a number like +3/5 or -6/7:");
#else
    printf("Input a number like +3/5 or -6/7:");
#endif
    if(choose)
        printf("%c: ",choose);
    unsigned int t1,t2;
    char sym;
    char iint;
    scanf("%c%u%c%u",&sym,&t1,&iint,&t2);
    getchar();

#ifdef EQUATION_IS_ON
    if(t1 == 0&&choose == 'a')
    {
        printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
#endif


    if(iint != 'i'&&t2 == 0)
    {
        printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
    if(iint == 'i')
    {
        a->numerator = t1;
        a->denominator = 1;
        if(t1 == 0)
        {
            a->symbol = '+';
            return;
        }
        a->symbol = sym;
        return;
    }
    a->numerator = t1;
    a->denominator = t2;
    a->symbol = sym;
    simp_frac(a);
}
unsigned long long gcd(unsigned long long a,unsigned long long b)
{
    return (b>0)?gcd(b,a%b):a;
}
void simp_frac(struct frac *a)
{
    unsigned long long gcd_ans = gcd(a->numerator,a->denominator);
    a->numerator /= gcd_ans;
    a->denominator /= gcd_ans;
}
void div_frac(struct frac a,struct frac b,struct frac *c)
{
    c->symbol = sym_choose_td(a.symbol,b.symbol);
    c->numerator = (a.numerator * b.denominator);
    c->denominator = (a.denominator * b.numerator);
    simp_frac(c);
}
char sym_choose_td(char a,char b)
{
    if(a == b)
        return '+';
    else
        return '-';
}
unsigned long long lcm(unsigned long long a,unsigned long long b)
{
    return (a*b / gcd(a,b));
}
void plus_frac(struct frac a,struct frac b,struct frac *c)
{
    RFCD(&a,&b);
    if(a.symbol == '+'&&b.symbol == '+')
    {
        c->numerator = a.numerator+b.numerator;
        c->denominator = a.denominator;
        c->symbol = '+';
    }
    else if(a.symbol == '+'&&b.symbol == '-')
    {
        if(comp_frac(a,b) == 1 || comp_frac(a,b) == 0)
        {
            c->numerator = a.numerator - b.numerator;
            c->denominator = a.denominator;
            c->symbol = '+';
        }
        else
        {
            c->numerator = b.numerator - a.numerator;
            c->denominator = a.denominator;
            c->symbol = '-';
        }
    }
    else if(a.symbol == '-'&&b.symbol == '-')
    {
        c->numerator = a.numerator + b.numerator;
        c->denominator = a.denominator;
        c->symbol = '-';
    }
    else if(a.symbol == '-'&&b.symbol == '+')
    {
        if(comp_frac(b,a) == 1 || comp_frac(a,b) == 0)
        {
            c->numerator = b.numerator - a.numerator;
            c->denominator = a.denominator;
            c->symbol = '+';
        }
        else
        {
            c->numerator = a.numerator - b.numerator;
            c->denominator = a.denominator;
            c->symbol = '-';
        }
    }
    simp_frac(c);
}
int comp_frac(struct frac a,struct frac b)
{
    RFCD(&a,&b);
    if(a.numerator > b.numerator)
        return 1;
    else if(a.numerator == b.numerator)
        return 0;
    else if(a.numerator < b.numerator)
        return -1;
    else return -2;
}
void RFCD(struct frac *a,struct frac *b)
{
    unsigned long long ta2,tb2,la,t1,t2;
    ta2 = a->denominator;
    tb2 = b->denominator;
    la = lcm(ta2,tb2);
    t1 = la / ta2;
    t2 = la / tb2;
    a->numerator *= t1;
    a->denominator *= t1;
    b->numerator *= t2;
    b->denominator *= t2;
}
void put_frac(struct frac a)
{
    if(a.denominator == 1)
    {
        if(a.numerator != 0)
            printf("%c%llu",a.symbol,a.numerator);
        else
            printf("0");
        return;
    }
    printf("%c%llu%c%llu",a.symbol,a.numerator,'/',a.denominator);
}
void make_frac(struct frac *a,unsigned b,unsigned c,char sym)
{
    a->symbol = sym;
    a->numerator = b;
    a->denominator = c;
}
void color_pchar(int I_color,int B_color,char mes)
{
    cset(I_color,B_color);
    putchar(mes);
    recset();
}
void sub_frac(struct frac a,struct frac b,struct frac *c)
{
    RFCD(&a,&b);
    if(b.symbol == '+')
        b.symbol = '-';
    else if(b.symbol == '-')
        b.symbol = '+';
    plus_frac(a,b,c);
}
void mul_frac(struct frac a,struct frac b,struct frac *c)
{
    c->numerator = a.numerator*b.numerator;
    c->denominator = a.denominator*b.denominator;
    c->symbol=sym_choose_td(a.symbol,b.symbol);
}
long long fact(int a)
{
    if (a > 0)
        return a * fact(a-1);
    else if(a == 0)
        return 1;
    else if(a < 0)
        return -1;
    else return -255;
}
#include <termio.h>

/*
 * 得到用户输入的一个字符
 *        : 返回得到字符
 */
int
getch(void) {
    int cr;
    struct termios nts, ots;

    if (tcgetattr(0, &ots) < 0) // 得到当前终端(0表示标准输入)的设置
        return EOF;

    nts = ots;
    cfmakeraw(&nts); // 设置终端为Raw原始模式，该模式下所有的输入数据以字节为单位被处理
    if (tcsetattr(0, TCSANOW, &nts) < 0) // 设置上更改之后的设置
        return EOF;

    cr = getchar();
    if (tcsetattr(0, TCSANOW, &ots) < 0) // 设置还原成老的模式
        return EOF;

    return cr;
}
bool bogo_sort(item *a,int size)
{
    int i,j;
    int tag;
#if DEBUG_MODE
    int debug_count = 1;
#endif
    if(a == NULL)
    {
        return false;
    }

    srand((unsigned int)time(NULL));
    while(1)
    {
#if DEBUG_MODE
        printf("\nDEBUG        :        %d\n",debug_count);
        print_num(a,size);
        printf("\n\n");
        debug_count++;
#endif
        tag = true;
        for(i = 1;i < size;i++)
        {
            if(a[i] < a[i - 1])
            {
                tag = false;
                break;
            }
        }
        if(tag){
            break;
        }
        for(i = 0;i < size;i++)
        {
            j = rand() % size;
            swap(a,i,j);
        }
    }
    return true;
}

void print_num(int a[],int size)
{
    int count = 0;
    while(1)
    {
        printf("%d ",a[count]);
        count++;
        if(count == size)
            break;
    }
}
void WHAT_DOSE_THIS_FUNC_REALLY_DO_(char c,int times)
{
    int count = 1;
    while(1){
        printf("%c",c);
        count++;
        if(count > times)
            break;
    }
}
int fxpd(void)
{
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
        return 1; //U
    }
    if(input[2] == 'B')
    {
        return 2; //D
    }
    if(input[2] == 'D')
    {
        return 3; //L
    }
    if(input[2] == 'C')
    {
        return 4; //R
    }
    return -1;
}
void PCTXY(char c,int x_rl,int y_dh,void (*prid) (void))
{
    cls();
    prid();
    WHAT_DOSE_THIS_FUNC_REALLY_DO_('\n',y_dh);
    WHAT_DOSE_THIS_FUNC_REALLY_DO_(' ',x_rl);
    putchar(c);
}
void cls(void)
{
    system("clear");
}
#ifdef PRIV
void print_m(void)
{

}
#else
void print_m(void)
{

}
#endif
void pzb(int x,int y)
{
    printf("(%d,%d)",x,y);
}
void PSCTXY(struct athing a,void (*prid) (void))
{
    PCTXY(a.c,a.x_rl,a.y_dh,prid);
}
void bPTH(struct athing *a,int x_rl,int y_dh,char c)
{
    a->x_rl = x_rl;
    a->y_dh = y_dh;
    a->c = c;
}
void WHAT_DOSE_THIS_FUNC_REALLY_DO_2(char *pstr,int times)
{
    int count = 1;
    while(1)
    {   count++;
        printf("%s",pstr);
        if(count > times)
            break;
    }
}
void pnl(void)
{
    printf("\n");
}
/*a:array,top_ind:数组最大下标，lx类型，randm最大值，sym：1：1-randm，0：0-randm，dight：d mode时位数*/
void ranari(int *a,int top_ind,int randm,int sym,int dight)
{
    static int ap = 0;
    if(top_ind < 0 || randm > RAND_MAX)
        error_func((d)1);
    if(ap == 0)
    {
        ap = 1;
        srand((unsigned int)time(NULL));
    }
    if(dight !=0)
        error_func((d)254);
    if(a == NULL)
        error_func((d)2);
    int count = 0;
    while(1)
    {
        if(sym == 0)
        {
            a[count] = rand() % (randm + 1);
        }
        else
        {
            a[count] = rand() % randm + 1;
        }
        count ++;
        if(count > top_ind)
        {
            break;
        }
    }
}
void ranarf(double *a,int top_ind)
{
    static int ap = 0;
    if(ap == 0)
    {
        ap = 1;
        srand((unsigned int)time(NULL));
    }
    if(top_ind < 0)
        error_func((d)1);
    if(a == NULL)
        error_func((d)2);
    int count = 0;
    int bcou = 0;
    int temp[3];
    while(1)
    {
        while(1)
        {
            temp[count] = rand() % 10;
            count ++;
            if(count == 3)
            {
                if(temp[0] == 0&&temp[1] == 0&&temp[2] == 0)
                {
                    count = 0;
                    continue;
                }
                break;
            }
        }
        a[bcou] = 0.0+(double)temp[0]/10+(double)temp[1]/100+(double)temp[2]/1000;
        bcou++;
        if(bcou > top_ind)
            break;
    }
}
void error_func(volatile sig_atomic_t errnum)
{
    emnum = errnum;
}
sig_atomic_t read_err(void)
{
    return emnum;
}
int is_file_exist(const char*file_path){
    if(file_path==NULL){
        return -1;
    }
    if(access(file_path,F_OK)==0){
        return 0;
    }
    return -1;
}
int is_dir_exist(const char*dir_path){
    if(dir_path==NULL){
        return -1;
    }
    if(opendir(dir_path)==NULL){
        return -1;
    }
    return 0;
}
//real_max_index == size - 1;
int all_thesame_i(int *a,int *b, int size)
{
    int count = 0;
    while(1)
    {
        if(a[count] != b[count])
            return count + 1;
        count++;
        if(count == size)
        {
            return 0;
        }
    }
}
void *nothing_todo(void *a)
{
    return a;
}
int count_same(int *a,int *b,int size)
{

    int error = 0;
    int count = 0;
    while(1)
    {
        if(a[count] != b[count])
            error++;
        count++;
        if(count == size)
        {
            return error;
        }

    }
}

void copy(int *src,int *to,int size)
{
    int count = 0;
    while(1)
    {
        to[count] = src[count];
        count++;
        if(count == size)
            return;
    }
}

void creat_linklist(struct node *a,int* dit,int array_size)
{
    dit = (int *)dit;
    printf("%p,%d,%d,%d\n",(void*)dit,dit[0],dit[1],dit[2]);
    creat_node2(a);
    int count = 0;
    while(1)
    {
        printf("%d\n",count);
        struct node *temp = NULL;
        a->data = dit[count];
        creat_node2(temp);
        creat_node1(a,temp);
        a = a->next;
        count++;
        if(count == array_size)
            return;
    }
}
void creat_node1(struct node *a,struct node *b)
{
    a->next = b;
    b->next = NULL;
}
void creat_node2(struct node *a)
{
    a = malloc(sizeof(struct node));
    a->data = 0;
    a->next = NULL;
}
void pll(struct node *a)
{
    printf("{");
    while(1)
    {
        printf("%d,",a->data);
        if(a->next == NULL)
            return;
        if(a->next->next == NULL)
            break;
        a = a->next;
    }
    a = a->next;
    printf("%d}",a->data);
    fflush(NULL);
    return;
}
