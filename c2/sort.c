#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRAY_LEN 30000

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
    sort_array(num);
    return 0;
}