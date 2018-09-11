#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#ifndef ARRAY_LEN
#define ARRAY_LEN 30000
#endif

void merge(int *a, int i1, int j1, int i2, int j2)
{
    int temp[ARRAY_LEN]; //array used for merging
    int i, j, k;
    i = i1; //beginning of the first list
    j = i2; //beginning of the second list
    k = 0;

    while (i <= j1 && j <= j2) //while elements in both lists
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= j1) //copy remaining elements of the first list
        temp[k++] = a[i++];

    while (j <= j2) //copy remaining elements of the second list
        temp[k++] = a[j++];

    //Transfer elements from temp[] back to a[]
    for (i = i1, j = 0; i <= j2; i++, j++)
        a[i] = temp[j];
}

void mergesort(int *a, int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
        mergesort(a, i, mid);         //left recursion
        mergesort(a, mid + 1, j);     //right recursion
        merge(a, i, mid, mid + 1, j); //merging of two sorted sub-arrays
    }
}

void sort_array()
{
    printf("Bubble sorting array of %d elements\n", ARRAY_LEN);
    int data[ARRAY_LEN], i;
    for (i = 0; i < ARRAY_LEN; ++i)
    {
        data[i] = rand();
    }
    mergesort(data, 0, ARRAY_LEN);
}

int main(int argc, char **argv)
{
    sort_array();
    return 0;
}