#ifndef FUNC_H
#define FUNC_H

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


#define MAX 27

#define CONSTANT 100
#define STRCON 2
#define PRIV 1
#define LINE 25

//#define DEBUG_MODE 1


#ifndef UNT8_SUPER_MODE

struct stack{
    char data[255];
    int top;
};

typedef double itemd;
typedef int item;
typedef unsigned int uitem;
typedef signed int sitem;
typedef volatile sig_atomic_t d;

#define I_BLACK 30
#define I_RED 31
#define I_GREEN 32
#define I_YELLOW 33
#define I_BLUE 34
#define I_PURPLE 35
#define I_DGREEN 36
#define I_WHITE 37

#define B_BLACK 40
#define B_DRED 41
#define B_GREEN 42
#define B_YELLOW 43
#define B_BLUE 44
#define B_PURPLE 45
#define B_DGREEN 46
#define B_WHITE 47

#define     ESC     "\033"
#define     UP      "\033[A"
#define     DOWN    "\033[B"
#define     LEFT    "\033[D"
#define     RIGHT   "\033[C"

#endif

#include <stdbool.h>


struct div_s{
    unsigned long long result;
    unsigned long long remainder;
};

struct frac{
    unsigned long long numerator;
    unsigned long long denominator;
    char symbol;
};

struct athing{
    char c;
    int x_rl;
    int y_dh;
};

struct pri_struct{
    bool is_f;
    bool is_d;
    int if_ishl;
};

void swap(item a[],int index1,int index2);
bool swap_safety(item a[],int size,int index1,int index2);
void bsort(item a[], int size);
long double abs_l(long double a);
struct div_s div_l(unsigned long long a,unsigned long long b);
bool istrb(char *a,int max_index);
bool istrs(char *a,int max_index);
void ceprint(int I_color,int B_color,char *mes);
//I_* -> I_color, B_* -> B_color
void cset(int I_color,int B_color);
void recset(void);
void color_pchar(int I_color,int B_color,char mes);
void cputchar(int I_color,int B_color,char meschar);


void input_frac(struct frac *a,int choose);
void simp_frac(struct frac *a);
unsigned long long gcd(unsigned long long a, unsigned long long b);
char sym_choose_td(char a,char b);
unsigned long long lcm(unsigned long long a,unsigned long long b);
void plus_frac(struct frac a,struct frac b,struct frac *c);
void sub_frac (struct frac a,struct frac b,struct frac *c);
void mul_frac (struct frac a,struct frac b,struct frac *c);
void div_frac (struct frac a,struct frac b,struct frac *c);
int comp_frac(struct frac a,struct frac b); //abs & comp.
void RFCD(struct frac *a,struct frac *b);//reduction of fractions to a common denominator
void put_frac(struct frac a);
void make_frac(struct frac *a, unsigned b, unsigned c, char sym);//it is used to debug

long long fact(int a);
int getch(void);

int bogo_sort(item *a,int size);
void print_num(int a[], int size, int sym,int sym2);
void print_num2(int a[],int size,int sym,int sym3,char x);
int fxpd(void);
void cls(void);
void PCTXY(char c, int x_rl, int y_dh,void (*prid)(void));
void print_m(void);
void pzb(int x,int y);
void PSCTXY(struct athing a,void (*prid) (void));
void bPTH(struct athing *a,int x_rl,int y_dh,char c);
void WHAT_DOSE_THIS_FUNC_REALLY_DO_(char c,int times);
void WHAT_DOSE_THIS_FUNC_REALLY_DO_2(char *pstr,int times);
void pnl(void);
void spe_WDTFRD2(char *pstr,int times,int x_rl,int y_dh);
void ranari(int *a, int top_ind, int randm, int sym, int dight);
void ranarf(double *a, int top_ind);
void error_func(volatile sig_atomic_t errnum);
sig_atomic_t read_err(void);
int is_file_exist(const char* file_path);
int is_dir_exist(const char* dir_path);
int all_thesame_i(int *a, int *b, int size);
void *nothing_todo(void *a);
int count_same(int *a,int *b,int size);
void copy_i(int *src,int *to,int size);
int t2t(char *two);
void copy_c(char *src,char *to);
void t2t2(int a, char b[]);

void stack_init(struct stack *a);
bool s_push(struct stack *a,char b);
char s_pop(struct stack *a);
int s_qtop(struct stack *a);
void pn(int a,int sym);

void copy_ic(int *src,char *to,int size);
void check_arg(int argc,char **argv);
void ReadStrUnit(char * str,char *temp_str,int idx,int len);
int GetSubStrPos(char *str1,char *str2);

void safe_gets(signed char *input,int len);
void itoa(long n, char *r);
void easy_fputs(char *x);
int pri_cs(const char *a);
int ftoa(char *str, double num, int n);
void pdouble(double x,int dight);
struct pri_struct double_test(char *x,int y);
#endif // FUNC_H



