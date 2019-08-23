#include "func.h"
#include "equation.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>
#include <stdbool.h>
#include <termios.h> //操作终端
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

static volatile sig_atomic_t emnum;
static struct div_s temp;
static bool has_input = false;
static struct pri_struct pri_temp;

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
#ifdef DEBUG_MODE
    int debug_count = 1;
#endif
    int out_count = 0;
    while(out_count != (size)*(size)){
        int this_index = 0;
        while(this_index < size - 1){
            if(a[this_index] > a[this_index + 1])
                swap(a,this_index,this_index + 1);
            this_index++;
#ifdef DEBUG_MODE
            printf("\nDEBUG        :        %d\n",debug_count);
            print_num(a,size,0,1);
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
    if (tcsetattr(0, TCSANOW, &ots) < 0) // 设置还原成元模式
        return EOF;

    return cr;
}
int bogo_sort(item *a,int size,int checkbit)
{
    if(checkbit == NULLCHAR)
    {
        return -1;
    }
    int i,j;
    int tag;
    int debug_count = 1;
    if(a == NULL)
    {
        return false;
    }

    srand((unsigned int)time(NULL));
    while(1)
    {
#ifdef DEBUG_MODE
        printf("\nDEBUG        :        %d\n",debug_count);
        print_num(a,size,0,1);
        printf("\n\n");
#endif
        debug_count++;
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
    return debug_count;
}

void print_num(int a[],int size,int sym,int sym2)
{
    int count = 0;
    if(sym2 != 0)
    {
        while(1)
        {
            printf("%d ",a[count]);
            count++;
            if(count == size)
                break;
        }
    }
    else
    {
        while(1)
        {
            printf("%d",a[count]);
            count++;
            if(count == size)
                break;
        }
    }
    if(sym == 1)
        puts("");
}
void print_num2(int a[],int size,int sym,int sym3,char x)
{
    int count = 0;
    if(sym3 != 0)
    {
        while(1)
        {
            printf("%d%c",a[count],x);
            count++;
            if(count == size)
                break;
        }
    }
    else {
        while(1)
        {
            printf("%d",a[count]);
            count++;
            if(count == size)
                break;
        }
    }
    if(sym == 1)
        puts("");
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
            //#define MODE
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
        count = 0;
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
int ats1i(int *a,int *b, int size)
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
int ats1i2(int *a,int *b,int size)
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

void copy_i(int *src,int *to,int size)
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

void copy_c(char *src,char *to)
{
    int count = 0;
    while(1)
    {
        to[count] = src[count];
        count++;
        if(src[count-1] == '\0')
            return;
    }
}
void copy_ic(int *src,char *to,int size) // NOT SAFE!!!!!!!!!!!
{
    int count = 0;
    while(1)
    {
        to[count] = (char)(src[count] + '0');
        count++;
        if(count == size)
            break;
    }
    to[size - 1] = '\0';
}
void f_array(int *a,int size,int start,int step)
{
    int count = 0;
    int a_a = start;
    while(1)
    {
        a[count] = a_a;
        a_a += step;
        if(count == size)
            break;
    }
}
int t2t(char *two)
{
    int num = 0, a = atoi(two), j=1;
    while(a)
    {
        num += (a%10) * j;
        a /= 10;
        j *= 2;
    }
    return num;
}
void t2t2(int a,char b[])
{
    int r,i=0,j=1,count[100];     //输入的是a
    do               //循环，直到a等于0跳出
    {
        r=a%2;       //求每一次的余数，实际上最后输出的也是这个
        a=a/2;
        i++;
        count[i]=r;

    }
    while(a!=0);
    //printf("十进制整数转换为二进制数是:\n");
    //if(i >= size - 1)
    //b = NULL;
    int count2 = 0;
    for(j=i;j>0;j--)                     //这里是倒序输出
    {
        b[count2] = (char)(count[j] + '0');
        count2++;
    }
    b[count2] = '\0';
}


void stack_init(struct stack *a)
{
    a = malloc(sizeof(struct stack));
    a->top = 0;
}
bool s_push(struct stack *a,char b)
{
    if(a->top == 255)
        return false;
    a->data[a->top] = b;
    a->top ++;
    return true;
}
char s_pop(struct stack *a)
{
    if(a->top == 0)
        return EOF;
    a->top --;
    return a->data[a->top];
}
//how many(1-xxx)
int s_qtop(struct stack *a)
{
    return a->top + 1;
}

void check_arg(int argc,char **argv)
{
    if(argc > 1&&strcmp(argv[1],"-run") == 0)
    {
        system("rm -rf ./.gcc_temp");
        int pid_status;
        pid_t i2 = fork();
        if(i2 == 0)
        {
            execl("/bin/mkdir","/bin/mkdir",".gcc_temp",NULL);
        }
        waitpid(i2,&pid_status,0);
        pid_t i = fork();
        if(i == 0)
        {
            execl("/bin/cp","/bin/cp",argv[2],"./.gcc_temp",NULL);
        }
        waitpid(i,&pid_status,0);
        pid_t i3 = fork();
        chdir("./.gcc_temp");
        if(i3 == 0)
        {
            execl("/bin/gcc","/bin/gcc",argv[2],NULL);
        }
        waitpid(i3,&pid_status,0);
        system("./a.out");
        chdir("..");
        system("rm -rf ./.gcc_temp");
    }
}

void pn(int a,int sym)
{
    printf("%d%c",a,sym==0?'\0':'\n');
}

static char temp_str[30];    // 临时子串

void ReadStrUnit(char * str,char *temp_str,int idx,int len)  // 从母串中获取与子串长度相等的临时子串
{
    int index;
    for(index = 0; index < len; index++)
    {
        temp_str[index] = str[idx+index];
    }
    temp_str[index] = '\0';
}

int GetSubStrPos(char *str1,char *str2)
{
    int idx = 0;
    int len1 = (int)strlen(str1);
    int len2 = (int)strlen(str2);

    if( len1 < len2)
    {
        return -1;
    }

    while(1)
    {
        ReadStrUnit(str1,temp_str,idx,len2);    // 不断获取的从 母串的 idx 位置处更新临时子串
        if(strcmp(str2,temp_str)==0)break;      // 若临时子串和子串一致，结束循环
        idx++;                                  // 改变从母串中取临时子串的位置
        if(idx>=len1)return -1;                 // 若 idx 已经超出母串长度，说明母串不包含该子串
    }

    return idx;    // 返回子串第一个字符在母串中的位置
}

void safe_gets(signed char *input,int len) //len:不包含'\0'
{
    int count = 0;
    while(1)
    {
        input[count] = (signed char)getchar();
        if(count >= len||input[count] == EOF||input[count] == '\n')
            break;
        count++;
    }
    input[count] = '\0';
}

struct pri_struct double_test(char *x,int y)
{
    if(x[y] == '%'&&x[y+1] == '.')
    {
        int count = y+2;
        while(1)
        {
            if(isdigit(x[count]) != true)
                break;
            count++;
        }
        int rs = count - (y+2);
        if(x[y+1+rs+1] == 'f')
            pri_temp.is_d = true;
        if(count == y+2)
        {
            pri_temp.is_f = false;
            return pri_temp;
        }
        pri_temp.is_f = true;
        pri_temp.if_ishl = count - (y+2);
        return pri_temp;
    }
    pri_temp.is_f = false;
    pri_temp.is_d = false;
    return pri_temp;
}
int pri_cs(const char *a)
{
    int size = cstrlen(int,a);
    int c2 = 0;
    int count = 0;
    while(1)
    {
        if(a[count] == '%')
        {
            if(count == 0||(count!=0&&a[count - 1] != '%'))
                c2++;
        }
        count++;
        if(count == size)
            break;
    }
    return c2;
}

void itoa(long n,char *r)
{
    char s[31];
    long i,j,sign;
    if((sign=n)<0)
        n=-n;
    i = 0;
    do{
        s[i++] = n % 10 + '0';
    }while((n /= 10)>0);
    if(sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    int count = 0;
    for(j = i-1;j >= 0;j--)
    {
        r[count] = s[j];
        count++;
    }
    r[count] = '\0';
}
int ftoa(char *str, double num, int n)        //n是转换的精度，即是字符串'.'后有几位小数
{
    int     sumI;
    double   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;

    char *p;
    char *pp;

    if(str == NULL) return -1;
    p = str;

    /*Is less than 0*/
    if(num < 0)
    {
        sign = 1;
        num = 0 - num;
    }

    sumI = (int)num;    //sumI is the part of int
    sumF = num - sumI;  //sumF is the part of double

    /*Int ===> String*/
    do
    {
        temp = sumI % 10;
        *(str++) = (char)(temp + '0');
    }while((sumI = sumI /10) != 0);


    /*******End*******/




    if(sign == 1)
    {
        *(str++) = '-';
    }

    pp = str;

    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }

    *(str++) = '.';     //point

    /*double ===> String*/
    do
    {
        temp = (int)(sumF*10);
        *(str++) = (char)(temp + '0');

        if((++count) == n)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));

    *(str) = '\0';

    return 0;
    /*
    版权声明：本文为CSDN博主「王大军9527」的原创文章，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/hui_love2046/article/details/5760907
    
    注：原本此函数有一个错误，导致其无法使用，现已更正
    */
}

void easy_fputs(char *x)
{
    int ct = 0;
    while(1)
    {
        putchar(x[ct]);
        ct++;
        if(x[ct] == '\0')
            break;
    }
}

void pdouble(double x,int dight)
{
    char y[65];
    ftoa(y,x,64);
    int count = 0;
    while(1)
    {
        putchar(y[count]);
        count++;
        if(y[count - 1] == '.')
            break;
    }
    int c2 = count;
    int c3 = c2;
    count = 0;
    int size = cstrlen(int,y);
    while(1)
    {
        putchar(y[c2]);
        c2++;
        count++;
        if(c2 == size - 1)
            break;
    }
    count = 0;
    while(1)
    {
        if(dight < size-c3)
            break;
        easy_fputs("0");
        count++;
        if(count ==    dight-(size-(c3)) + 1)
            break;
    }
}

void pri_da(double *a,int size,int dight,bool flag1,bool flag2,int arg_f1)
{
    int count = 0;
    while(1)
    {
        if(flag2 == false)
        {
            if(arg_f1 != 0x12c76dc)
                exit(EXIT_FAILURE);
            printf("%.*f ",dight,a[count]);
        }
        else {
            printf("%.*f%c",dight,a[count],(char)arg_f1);
        }
        count++;
        if(count == size)
            break;
    }
    if(flag1 == true)
        pnl();
}

void rev_str(char *x,char *to)
{
    int size = cstrlen(int,x) - 1;
    int count = 0;
    while(1)
    {
        to[count] = x[size];
        count++;
        size --;
        if(size < 0)
            break;
    }
}
__int128 readbi()
{
    __int128 x=0,f=1;
    char ch=cht getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=cht getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0'; ch=cht getchar();
    }
    return x*f;
}
void printbi(__int128 x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
        printbi(x/10);
    putchar(x%10+'0');
    /*版权声明：printbi(),readbi()为CSDN博主「傻蛋的阿简」的原创文章(里的函数)，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/shadandeajian/article/details/81843805*/
}


void parrayc(int b,int c,char a[][c],int flag1)
{
    int co = 0;
    int ci = 0;
    while(1)
    {
        while(1)
        {
            if(flag1 == 0)
                printf("%c ",a[co][ci]);
            else
            {
                if(a[co][ci] == 'N')
                    ceprint(I_BLACK,B_GREEN,"N ");
                else if(a[co][ci] == 'Y')
                    ceprint(I_BLACK,B_DRED,"Y ");
                else
                {
                    printf("%c ",a[co][ci]);
                }
            }
            fflush(NULL);
            ci++;
            if(ci == c)
                break;
        }
        pnl();
        ci = 0;
        co++;
        if(co == b)
            break;
    }
}
struct coordinates conversion(struct coordinates a,int xmax,int ymax)
{
    (void)xmax;
    coor temp;
    temp.x = ymax - 1 - a.y;
    temp.y = a.x;
    return temp;
}

bool ats2(int x,int y,const char a[x][y],char b)
{
    int co = 0,ci = 0;
    while(1)
    {
        while(1)
        {
            char t = a[co][ci];
            if(t != b)
            {
                //printf("%d,%d:FALSE:%c and %c\n",co,ci,t,b);
                return false;
            }
            //printf("%d,%d:TRUE\n",co,ci);
            ci++;
            if(ci == y)
                break;
        }
        ci = 0;
        co++;
        if(co == x)
            break;
    }
    return true;
}
void fillarray2(int x,int y,char a[x][y],char b)
{
    int co = 0,ci = 0;
    while(1)
    {
        while(1)
        {
            a[co][ci] = b;
            ci++;
            if(ci == y)
                break;
        }
        ci = 0;
        co++;
        if(co == x)
            break;
    }

}
