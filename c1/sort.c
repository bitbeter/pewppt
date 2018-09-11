#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRAY_LEN 30000

static struct timeval tm1;

static inline void start()
{
    gettimeofday(&tm1, NULL);
}

static inline void stop()
{
    struct timeval tm2;
    gettimeofday(&tm2, NULL);
    unsigned long long t = 1000 * (tm2.tv_sec - tm1.tv_sec) +
                           (tm2.tv_usec - tm1.tv_usec) / 1000;
    printf("%llu ms\n", t);
}

void bubble_sort(int *a, int n)
{
    int i, t, s = 1;
    while (s)
    {
        s = 0;
        for (i = 1; i < n; i++)
        {
            if (a[i] < a[i - 1])
            {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }
}

void sort_array(int numberOfElements)
{
    printf("Bubble sorting array of %d elements\n", numberOfElements);
    int data[numberOfElements], i;
    for (i = 0; i < numberOfElements; ++i)
    {
        data[i] = rand();
    }
    bubble_sort(data, numberOfElements);
}

int main(int argc, char **argv)
{
    int num = ARRAY_LEN;
    if (argc > 1)
    {
        sscanf(argv[1], "%d", &num);
    }
    start();
    sort_array(num);
    stop();
    return 0;
}