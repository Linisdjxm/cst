#include <sys/types.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "sprog.h"
#include "func.h"
#include "equation.h"

int main(void)
{
    int a[10];
    ranari(a,9,9,0,0);
    struct node * t1 = NULL;
    creat_linklist(t1,(int *)a,10);
    pll(t1);
    return 0;
}
