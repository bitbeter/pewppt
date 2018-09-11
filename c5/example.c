#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define F1 30000
#define F2 90000

void f1()
{
    int i;
    double sum = 1;
    for (i = 0; i < F1; ++i)
    {
        sum *= 1.1;
    }
}

void f2()
{
    int i;
    double sum = 1;
    for (i = 0; i < F2; ++i)
    {
        sum *= 1.1;
    }
}

int main(int argc, char **argv)
{
    while (1)
    {
        f1();
        f2();
    }
    return 0;
}