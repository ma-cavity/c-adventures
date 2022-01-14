#ifndef C_ADVENTURES_SELECTION_SORT_H
#define C_ADVENTURES_SELECTION_SORT_H

#include <stdio.h>
#include <string.h>

void swap(unsigned short int* xp, unsigned short int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(unsigned short int arr[], unsigned short int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(unsigned short int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        arr[i] != 0 && printf("%d ", arr[i]);
    printf("\n");
}

#endif